#ifndef __WIN_SEH_H
#define __WIN_SEH_H

#include "buffer.h"

#define SEH_MAGIC 0xBABEFACE

#define SIZEOF_387_REGS      80
#define MAXIMUM_EXTENSION    512

//Some exception codes

//Read or write memory violation
#define MEM_ACCESS 0xC0000005   

//Divide by zero
#define DIV_ZERO_EXCEPTION 0xC0000094   

//Divide overflow
#define DIV_OFLOW 0xC0000095   

//The stack went beyond the maximum available size
#define STACK_OVERFLOW 0xC00000FD   

//Violation of a guard page in memory set up using Virtual Alloc
#define GUARD_ERROR 0x80000001   

//The following only occur whilst dealing with exceptions:-

//A non-continuable exception: the handler should not try to deal with it
#define NON_CONT 0xC0000025    

//Exception code used the by system during exception handling. This code might
//be used if the system encounters an unexpected return from a handler. It is
//also used if no Exception Record is supplied when calling RtlUnwind.
#define EXC_EXC 0xC0000026   

//The following are used in debugging:-

//Breakpoint occurred because there was an INT3 in the code
#define BREAKPOINT_EXCEPTION 0x80000003   

//Single step during debugging
#define DEBUG_EXCEPTION 0x80000004   

#define CONTINUABLE 0
#define NON_CONTINUABLE 1
#define STACK_UNWINDING 2

struct FLOATING_SAVE_AREA {
   dword   ControlWord;
   dword   StatusWord;
   dword   TagWord;
   dword   ErrorOffset;
   dword   ErrorSelector;
   dword   DataOffset;
   dword   DataSelector;
   byte    RegisterArea[SIZEOF_387_REGS];
   dword   Cr0NpxState;
};

struct CONTEXT {

   dword ContextFlags;

   dword   Dr0;
   dword   Dr1;
   dword   Dr2;
   dword   Dr3;
   dword   Dr6;
   dword   Dr7;

   FLOATING_SAVE_AREA FloatSave;

   dword   SegGs;
   dword   SegFs;
   dword   SegEs;
   dword   SegDs;

   dword   Edi;   //0x9C
   dword   Esi;   //0xA0
   dword   Ebx;   //0xA4
   dword   Edx;   //0xA8
   dword   Ecx;   //0xAC
   dword   Eax;   //0xB0

   dword   Ebp;   //0xB4
   dword   Eip;   //0xB8
   dword   SegCs;
   dword   EFlags;
   dword   Esp;
   dword   SegSs;

   byte   ExtendedRegisters[MAXIMUM_EXTENSION];

};

#define MAXIMUM_PARMS 15

struct EXCEPTION_RECORD {
   dword exceptionCode;
   dword exceptionFlags;
   dword exceptionRecord;  //struct _EXCEPTION_RECORD *ExceptionRecord
   dword exceptionAddress;
   dword numberParameters;
   dword exceptionInformation[MAXIMUM_PARMS];
};

struct EXCEPTION_POINTERS {
   EXCEPTION_RECORD *exceptionRecord;
   CONTEXT *contextRecord;
};

struct ERR {
   dword nextErr;  //struct _ERR *nextErr;
   dword handler;  //pointer to handler
};   

int usingSEH();
void sehBegin(dword interrupt_number);
void sehReturn();
void breakpointException();
void debugException();
void divzeroException();
void memoryAccessException();
void enableSEH();
void saveSEHState(Buffer &b);
void loadSEHState(Buffer &b);
struct CONTEXT *getContext();

#endif
