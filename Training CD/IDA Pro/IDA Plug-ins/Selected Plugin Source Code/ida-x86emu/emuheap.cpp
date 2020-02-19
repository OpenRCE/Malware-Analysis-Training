/*
   Source for x86 emulator IdaPro plugin
   File: emuheap.cpp
   Copyright (c) 2004, Chris Eagle
   
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 2 of the License, or (at your option) 
   any later version.
   
   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
   FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for 
   more details.
   
   You should have received a copy of the GNU General Public License along with 
   this program; if not, write to the Free Software Foundation, Inc., 59 Temple 
   Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include <stdlib.h>
#include <string.h>

#include "emuheap.h"

#include <kernwin.hpp>

//Constructor for malloc'ed node
MallocNode::MallocNode(unsigned int size, unsigned int base) {
   this->base = base;
   this->size = size;
   block = (unsigned char*) malloc(size);
}

MallocNode::MallocNode(Buffer &b) {
   b.read((char*)&base, sizeof(base));
   b.read((char*)&size, sizeof(size));
   block = (unsigned char*) malloc(size);
   b.read((char*)block, size);
}

void MallocNode::save(Buffer &b) {
   b.write((char*)&base, sizeof(base));
   b.write((char*)&size, sizeof(size));
   b.write((char*)block, size);
}

//malloc'ed node destructor
MallocNode::~MallocNode() {
   free(block);
}

//Does this block contain the indicated virtual address?
bool MallocNode::contains(unsigned int addr) {
   return (addr - base) < size;
}

//Read a byte from this block
unsigned char MallocNode::readByte(unsigned int addr) {
   unsigned char val = 0;
   if (contains(addr)) {
      val = block[addr - base];
   }
   return val;
}

//write a byte to this block
void MallocNode::writeByte(unsigned int addr, unsigned char val) {
   if (contains(addr)) {
      block[addr - base] = val;
   }
}

//Emulation heap constructor, indicate virtual address of base and max size
EmuHeap::EmuHeap(unsigned int baseAddr, unsigned int maxSize, EmuHeap *next) {
   head = NULL;
   base = baseAddr;
   max = base + maxSize;
   nextHeap = next;
}

EmuHeap::EmuHeap(Buffer &b, unsigned int num_blocks) {
   nextHeap = NULL;
   readHeap(b, num_blocks);
}

//Construct new heap from binary buffer data
EmuHeap::EmuHeap(Buffer &b) {
   unsigned int n;
   nextHeap = NULL;
   head = NULL;
   b.read((char*)&n, sizeof(n));
   
   //test for multi-heap
   if (n == HEAP_MAGIC) {
      unsigned int num_heaps;
      EmuHeap *p = NULL;
      b.read((char*)&num_heaps, sizeof(num_heaps));
      for (unsigned int i = 0; i < num_heaps; i++) {
         b.read((char*)&n, sizeof(n));
         if (p) {
            p->nextHeap = new EmuHeap(b, n);
            p = p->nextHeap;
         }
         else {
            readHeap(b, n);
            p = this;
         }
      }
   }
   else { //only a single heap, we already have n
      readHeap(b, n);
   }
}

//read a head consisting of num_blocks allocated blocks from a buffer
void EmuHeap::readHeap(Buffer &b, unsigned int num_blocks) {
   b.read((char*)&base, sizeof(base));
   b.read((char*)&max, sizeof(max));
   for (unsigned int i = 0; i < num_blocks; i++) {
      insert(new MallocNode(b));
   }
}

//dump a heap to a buffer
void EmuHeap::writeHeap(Buffer &b) {
   unsigned int n = 0;
   MallocNode *m;
   for (m = head; m; m = m->next) n++;
   b.write((char*)&n, sizeof(n));
   b.write((char*)&base, sizeof(base));
   b.write((char*)&max, sizeof(max));
   for (m = head; m; m = m->next) {
      m->save(b);
   }
}

//Save existing heap to binary buffer
void EmuHeap::save(Buffer &b) {
   unsigned int num_heaps = 0;
   unsigned int magic = HEAP_MAGIC;
   EmuHeap *h;
   
   //count the number of heaps
   for (h = this; h; h = h->nextHeap) num_heaps++;

   //if more than one heap, then use multi-heap format
   if (num_heaps > 1) {
      b.write((char*)&magic, sizeof(magic));
      b.write((char*)&num_heaps, sizeof(num_heaps));
   }
   
   //write all of the heaps
   for (h = this; h; h = h->nextHeap) {
      h->writeHeap(b);
   }  
}

//Destructor for the emulator heap
EmuHeap::~EmuHeap() {
   if (nextHeap) {
      delete nextHeap;
   }
   MallocNode *p, *t = head;
   while (t) {
      p = t;
      t = t->next;
      delete p;
   }
}

//Read a byte out of the emulation heap
unsigned char EmuHeap::readByte(unsigned int addr) {
   //first find the node containng the byte, then read it
   MallocNode *node = findNode(addr);
   if (node) {
      return node->readByte(addr);
   }
   else {
      //oops, attempted access to unallocated memory!
   }
   return 0;
}

//write a byte to the emulation heap
void EmuHeap::writeByte(unsigned int addr, unsigned char val) {
   //first find the node, then write the byte
   MallocNode *node = findNode(addr);
   if (node) {
      node->writeByte(addr, val);
   }
   else {
      //oops, writing to unallocated memory!
   }
}

//Emulation heap malloc function
unsigned int EmuHeap::malloc(unsigned int size) {
   size = (size + 3) & 0xFFFFFFFC;  //round up to word boundary
   //find a gap that we can fit in
   unsigned int addr = findBlock(size);
   if (addr != HEAP_ERROR) {
      //create and insert a new malloc node into the allocation list
      insert(new MallocNode(size, addr));
   }
   return addr;
}

//Emulation heap calloc function
unsigned int EmuHeap::calloc(unsigned int nmemb, unsigned int size) {
   //first malloc the block
   unsigned int addr = this->malloc(nmemb * size);
   if (addr != HEAP_ERROR) {
      //find the newly malloc'ed block and zeroize it
      MallocNode *node = findMallocNode(addr); //this should never fail
      memset(node->block, 0, node->size);
   }
   return addr;
}

//emulation heap free function
unsigned int EmuHeap::free(unsigned int addr) {
   if (addr) {
      MallocNode *p = NULL, *t = head;
      //look for the matching malloc'ed block
      while (t) {
         //supplied address must be the base of a malloc'ed block
         if (t->base == addr) {
            //unlink the malloc'ed node
            if (p) {
               p->next = t->next;
            }
            else {
               head = t->next;
            }
            //free the malloc'ed memory
            delete t;
            break;
         }
         p = t;
         t = t->next;
      }
      if (t == NULL) addr = 0;
   }
   return addr;
}

//emulations heap realloc function
unsigned int EmuHeap::realloc(unsigned int ptr, unsigned int size) {
   unsigned int result = HEAP_ERROR;
   if (ptr == 0) {
      //act like malloc is ptr is NULL
      result = this->malloc(size);
   }
   else {
      //find the malloc'ed node
      MallocNode *node = findMallocNode(ptr);
      //round the new size to a word boundary
      size = (size + 3) & 0xFFFFFFFC;
      if (node) {
         if (size == node->size) {
            //no change in size? do nothing
            result = ptr;
         }
         else if (size < node->size) {
            //node shrinking, shrink node size and realloc its block
            node->size = size;
            node->block = (unsigned char*) ::realloc(node->block, size);
            result = ptr;
         }
         else {
            //node growing, allocate new block
            result = this->malloc(size);
            if (result != HEAP_ERROR) {
               //find the newly allocated node
               MallocNode *newnode = findMallocNode(result);
               //copy the old block into the new larger block
               memcpy(newnode->block, node->block, node->size);
               //free the old block
               this->free(ptr);
            }
         }
      }
   }
   return result;
}

EmuHeap *EmuHeap::contains(unsigned int addr) {
   EmuHeap *h;
   for (h = this; h; h = h->nextHeap) {
      if ((addr >= h->base) && (addr < h->max)) return h;
   }
   return NULL;
}

//insert a newly malloc'ed node into the allocation list
//the list is sorted by increasing base address
void EmuHeap::insert(MallocNode *node) {
   MallocNode *p = NULL, *t = head;
   while (t && t->base < node->base) {
      p = t;
      t = t->next;
   }
   node->next = t;
   if (p) {
      p->next = node;
   }
   else {
      head = node;
   }
}

//find the malloc'ed node containing the specified address
MallocNode *EmuHeap::findNode(unsigned int addr) {
   MallocNode *result = NULL;
   for (MallocNode *p = head; p; p = p->next) {
      if (p->contains(addr)) {
         result = p;
         break;
      }
   }
   return result;
}

//find the malloc'ed node based at the specified address
MallocNode *EmuHeap::findMallocNode(unsigned int addr) {
   MallocNode *result = NULL;
   for (MallocNode *p = head; p; p = p->next) {
      if (p->base == addr) {
         result = p;
         break;
      }
   }
   return result;
}

//locate a block large enough to satisfy the caller's request
//keep a 4 byte gap between all blocks in order to detect overflows
unsigned int EmuHeap::findBlock(unsigned int size) {
   unsigned int result = HEAP_ERROR;
   MallocNode *p;
   //first see if we can fit in a gap between exiting blocks
   for (p = head; p && p->next; p = p->next) {
      unsigned int gap = p->next->base - (p->base + p->size);
      if ((size + 8) <= gap) {
         break;
      }
   }
   if (p) {
      //compute the start address of the block
      unsigned int nextBase = p->base + p->size + 4;
      if ((nextBase + size) < max) {
         //success only if we are not out of memory
         result = nextBase;
      }
   }
   else { //first block goes at the base of the heap
      if ((base + size) < max) {
         result = base;
      }
   }
   return result;
}


