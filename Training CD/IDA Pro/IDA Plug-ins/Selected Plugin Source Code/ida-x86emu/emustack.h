/*
   Source for x86 emulator IdaPro plugin
   File: emustack.h
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


#ifndef EMUSTACK_H
#define EMUSTACK_H

#include <stdio.h>
#include "buffer.h"

class EmuStack {
public:
   EmuStack(unsigned int stackTop, unsigned int maxSize);
   EmuStack(Buffer &b);
   ~EmuStack();

   void rebase(unsigned int stackTop, unsigned int maxSize);
   bool contains(unsigned int addr);
   unsigned int getStackTop() {return top;};
   unsigned int getStackSize() {return maxSize;};
   unsigned char readByte(unsigned int addr);
   void writeByte(unsigned int addr, unsigned char val);

   void save(Buffer &b, unsigned int sp);

private:
   unsigned char *stack;
   unsigned int top;
   unsigned int bottom;
   unsigned int maxSize;
   unsigned int allocated;

};


#endif

