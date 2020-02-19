/*
   Source for x86 emulator IdaPro plugin
   File: emustack.cpp
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
#include "emustack.h"

#define BLOCK_INCREMENT 0x1000

EmuStack::EmuStack(unsigned int stackTop, unsigned int maxSize) {
   top = stackTop;
   this->maxSize = maxSize;
   bottom = top - maxSize;
   allocated = maxSize < 0x8000 ? maxSize : 0x8000;
   stack = (unsigned char*) malloc(allocated);
}

EmuStack::EmuStack(Buffer &b) {
   unsigned int sp;
   b.read((char*)&sp, sizeof(sp));
   b.read((char*)&top, sizeof(top));
   b.read((char*)&bottom, sizeof(bottom));
   b.read((char*)&maxSize, sizeof(maxSize));
   b.read((char*)&allocated, sizeof(allocated));
   stack = (unsigned char*) malloc(allocated);
   b.read((char*)stack, top - sp);
}

void EmuStack::save(Buffer &b, unsigned int sp) {
   b.write((char*)&sp, sizeof(sp));
   b.write((char*)&top, sizeof(top));
   b.write((char*)&bottom, sizeof(bottom));
   b.write((char*)&maxSize, sizeof(maxSize));
   b.write((char*)&allocated, sizeof(allocated));
   b.write((char*)stack, top - sp);
}

EmuStack::~EmuStack() {
   free(stack);
}

void EmuStack::rebase(unsigned int stackTop, unsigned int maxSize) {
   top = stackTop;
   if (maxSize < allocated) {
      stack = (unsigned char*) realloc(stack, maxSize);
      allocated = maxSize;
   }
   this->maxSize = maxSize;
   bottom = top - maxSize;
}

bool EmuStack::contains(unsigned int addr) {
   return (addr < top) && (addr >= bottom);
}

unsigned char EmuStack::readByte(unsigned int addr) {
   unsigned int internal = top - addr;
   return internal > allocated ? 0 : stack[internal - 1];
}

void EmuStack::writeByte(unsigned int addr, unsigned char val) {
   unsigned int internal = top - addr;
   if (internal > allocated) {
      //allocate to next BLOCK_INCREMENT boundary above internal
      allocated = (internal + BLOCK_INCREMENT) & ~(BLOCK_INCREMENT - 1);
      stack = (unsigned char*) realloc(stack, allocated);
   }
   stack[internal - 1] = val;
}


