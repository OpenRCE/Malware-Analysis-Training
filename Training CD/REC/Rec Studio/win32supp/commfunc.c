/* 
   CommonFunctions.h

   Declarations for all the Windows32 API Functions that do not have
   separate ANSI and UNICODE versions.

   Copyright (C) 1996, 1997, 1998 Free Software Foundation, Inc.

   Author: Scott Christley <scottc@net-community.com>

   This file is part of the Windows32 API Library.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   If you are interested in a warranty or support for this source code,
   contact Scott Christley <scottc@net-community.com> for more information.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; see the file COPYING.LIB.
   If not, write to the Free Software Foundation, 
   59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/ 

#ifndef _GNU_H_WINDOWS32_COMMONFUNCTIONS
#define _GNU_H_WINDOWS32_COMMONFUNCTIONS

/* Skip if invoked by resource compiler */
#ifndef RC_INVOKED

#include <stdarg.h>
#include "Defines.h"
#include "Base.h"
#include "wstructs.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

WINBOOL STDCALL AbnormalTermination(VOID) {}
/* int STDCALL AbortDoc(HDC hDC) {} */
/*WINBOOL STDCALL AbortPath(HDC hDC) {}*/
WINBOOL STDCALL AbortPrinter(HANDLE h) {}
WINBOOL CALLBACK AbortProc(HDC hDC, int v) {}
WINBOOL STDCALL AbortSystemShutdown(LPTSTR str) {}
/* WINBOOL STDCALL AccessCheck(
		    PSECURITY_DESCRIPTOR  pSecurityDescriptor,
		    HANDLE  ClientToken,
		    DWORD  DesiredAccess,
		    PGENERIC_MAPPING  GenericMapping,
		    PPRIVILEGE_SET  PrivilegeSet,
		    LPDWORD  PrivilegeSetLength,
		    LPDWORD  GrantedAccess,
		    LPBOOL  AccessStatus
		    ) {} */

WINBOOL STDCALL AccessCheckAndAuditAlarm(
				 LPCTSTR  SubsystemName,
				 LPVOID  HandleId,
				 LPTSTR  ObjectTypeName,
				 LPTSTR  ObjectName,
				 PSECURITY_DESCRIPTOR  SecurityDescriptor,
				 DWORD  DesiredAccess,
				 PGENERIC_MAPPING  GenericMapping,
				 WINBOOL  ObjectCreation,
				 LPDWORD  GrantedAccess,
				 LPBOOL  AccessStatus,
				 LPBOOL  pfGenerateOnClose
				 ) {}

LONG
STDCALL
InterlockedIncrement(
		     LPLONG lpAddend
		     ) {}

LONG
STDCALL
InterlockedDecrement(
		     LPLONG lpAddend
		     ) {}

LONG
STDCALL
InterlockedExchange(
		    LPLONG Target,
		    LONG Value
		    ) {}

WINBOOL
STDCALL
FreeResource(
	     HGLOBAL hResData
	     ) {}

LPVOID
STDCALL
LockResource(
	     HGLOBAL hResData
	     ) {}

int
STDCALL
WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd
	) {}

WINBOOL
STDCALL
FreeLibrary(
	    HINSTANCE hLibModule
	    ) {}


VOID
STDCALL
FreeLibraryAndExitThread(
			 HMODULE hLibModule,
			 DWORD dwExitCode
			 ) {}

WINBOOL
STDCALL
DisableThreadLibraryCalls(
			  HMODULE hLibModule
			  ) {}

FARPROC
STDCALL
GetProcAddress(
	       HINSTANCE hModule,
	       LPCSTR lpProcName
	       ) {}

DWORD
STDCALL
GetVersion( VOID ) {}

HGLOBAL
STDCALL
GlobalAlloc(
	    UINT uFlags,
	    DWORD dwBytes
	    ) {}

HGLOBAL
GlobalDiscard(
	      HGLOBAL hglbMem
	      ) {}

HGLOBAL
STDCALL
GlobalReAlloc(
	      HGLOBAL hMem,
	      DWORD dwBytes,
	      UINT uFlags
	      ) {}

DWORD
STDCALL
GlobalSize(
	   HGLOBAL hMem
	   ) {}

UINT
STDCALL
GlobalFlags(
	    HGLOBAL hMem
	    ) {}


LPVOID
STDCALL
GlobalLock(
	   HGLOBAL hMem
	   ) {}

HGLOBAL
STDCALL
GlobalHandle(
	     LPCVOID pMem
	     ) {}


WINBOOL
STDCALL
GlobalUnlock(
	     HGLOBAL hMem
	     ) {}


HGLOBAL
STDCALL
GlobalFree(
	   HGLOBAL hMem
	   ) {}

UINT
STDCALL
GlobalCompact(
	      DWORD dwMinFree
	      ) {}


VOID
STDCALL
GlobalFix(
	  HGLOBAL hMem
	  ) {}


VOID
STDCALL
GlobalUnfix(
	    HGLOBAL hMem
	    ) {}


LPVOID
STDCALL
GlobalWire(
	   HGLOBAL hMem
	   ) {}


WINBOOL
STDCALL
GlobalUnWire(
	     HGLOBAL hMem
	     ) {}


VOID
STDCALL
GlobalMemoryStatus(
		   LPMEMORYSTATUS lpBuffer
		   ) {}


HLOCAL
STDCALL
LocalAlloc(
	   UINT uFlags,
	   UINT uBytes
	   ) {}

HLOCAL
LocalDiscard(
	     HLOCAL hlocMem
	     ) {}

HLOCAL
STDCALL
LocalReAlloc(
	     HLOCAL hMem,
	     UINT uBytes,
	     UINT uFlags
	     ) {}


LPVOID
STDCALL
LocalLock(
	  HLOCAL hMem
	  ) {}


HLOCAL
STDCALL
LocalHandle(
	    LPCVOID pMem
	    ) {}


WINBOOL
STDCALL
LocalUnlock(
	    HLOCAL hMem
	    ) {}


UINT
STDCALL
LocalSize(
	  HLOCAL hMem
	  ) {}


UINT
STDCALL
LocalFlags(
	   HLOCAL hMem
	   ) {}


HLOCAL
STDCALL
LocalFree(
	  HLOCAL hMem
	  ) {}


UINT
STDCALL
LocalShrink(
	    HLOCAL hMem,
	    UINT cbNewSize
	    ) {}


UINT
STDCALL
LocalCompact(
	     UINT uMinFree
	     ) {}


WINBOOL
STDCALL
FlushInstructionCache(
		      HANDLE hProcess,
		      LPCVOID lpBaseAddress,
		      DWORD dwSize
		      ) {}


LPVOID
STDCALL
VirtualAlloc(
	     LPVOID lpAddress,
	     DWORD dwSize,
	     DWORD flAllocationType,
	     DWORD flProtect
	     ) {}


WINBOOL
STDCALL
VirtualFree(
	    LPVOID lpAddress,
	    DWORD dwSize,
	    DWORD dwFreeType
	    ) {}


WINBOOL
STDCALL
VirtualProtect(
	       LPVOID lpAddress,
	       DWORD dwSize,
	       DWORD flNewProtect,
	       PDWORD lpflOldProtect
	       ) {}


DWORD
STDCALL
VirtualQuery(
	     LPCVOID lpAddress,
	     PMEMORY_BASIC_INFORMATION lpBuffer,
	     DWORD dwLength
	     ) {}


WINBOOL
STDCALL
VirtualProtectEx(
		 HANDLE hProcess,
		 LPVOID lpAddress,
		 DWORD dwSize,
		 DWORD flNewProtect,
		 PDWORD lpflOldProtect
		 ) {}


DWORD
STDCALL
VirtualQueryEx(
	       HANDLE hProcess,
	       LPCVOID lpAddress,
	       PMEMORY_BASIC_INFORMATION lpBuffer,
	       DWORD dwLength
	       ) {}


HANDLE
STDCALL
HeapCreate(
	   DWORD flOptions,
	   DWORD dwInitialSize,
	   DWORD dwMaximumSize
	   ) {}

WINBOOL
STDCALL
HeapDestroy(
	    HANDLE hHeap
	    ) {}

LPVOID
STDCALL
HeapAlloc(
	  HANDLE hHeap,
	  DWORD dwFlags,
	  DWORD dwBytes
	  ) {}

LPVOID
STDCALL
HeapReAlloc(
	    HANDLE hHeap,
	    DWORD dwFlags,
	    LPVOID lpMem,
	    DWORD dwBytes
	    ) {}

WINBOOL
STDCALL
HeapFree(
	 HANDLE hHeap,
	 DWORD dwFlags,
	 LPVOID lpMem
	 ) {}

DWORD
STDCALL
HeapSize(
	 HANDLE hHeap,
	 DWORD dwFlags,
	 LPCVOID lpMem
	 ) {}

WINBOOL
STDCALL
HeapValidate(
	     HANDLE hHeap,
	     DWORD dwFlags,
	     LPCVOID lpMem
	     ) {}

UINT
STDCALL
HeapCompact(
	    HANDLE hHeap,
	    DWORD dwFlags
	    ) {}

HANDLE
STDCALL
GetProcessHeap( VOID ) {}

DWORD
STDCALL
GetProcessHeaps(
		DWORD NumberOfHeaps,
		PHANDLE ProcessHeaps
		) {}

WINBOOL
STDCALL
HeapLock(
	 HANDLE hHeap
	 ) {}

WINBOOL
STDCALL
HeapUnlock(
	   HANDLE hHeap
	   ) {}

WINBOOL
STDCALL
HeapWalk(
	 HANDLE hHeap,
	 LPPROCESS_HEAP_ENTRY lpEntry
	 ) {}

WINBOOL
STDCALL
GetProcessAffinityMask(
		       HANDLE hProcess,
		       LPDWORD lpProcessAffinityMask,
		       LPDWORD lpSystemAffinityMask
		       ) {}

WINBOOL
STDCALL
GetProcessTimes(
		HANDLE hProcess,
		LPFILETIME lpCreationTime,
		LPFILETIME lpExitTime,
		LPFILETIME lpKernelTime,
		LPFILETIME lpUserTime
		) {}

WINBOOL
STDCALL
GetProcessWorkingSetSize(
			 HANDLE hProcess,
			 LPDWORD lpMinimumWorkingSetSize,
			 LPDWORD lpMaximumWorkingSetSize
			 ) {}

WINBOOL
STDCALL
SetProcessWorkingSetSize(
			 HANDLE hProcess,
			 DWORD dwMinimumWorkingSetSize,
			 DWORD dwMaximumWorkingSetSize
			 ) {}

HANDLE
STDCALL
OpenProcess(
	    DWORD dwDesiredAccess,
	    WINBOOL bInheritHandle,
	    DWORD dwProcessId
	    ) {}

HANDLE
STDCALL
GetCurrentProcess(
		  VOID
		  ) {}

DWORD
STDCALL
GetCurrentProcessId(
		    VOID
		    ) {}

VOID
STDCALL
ExitProcess(
	    UINT uExitCode
	    ) {}

WINBOOL
STDCALL
TerminateProcess(
		 HANDLE hProcess,
		 UINT uExitCode
		 ) {}

WINBOOL
STDCALL
GetExitCodeProcess(
		   HANDLE hProcess,
		   LPDWORD lpExitCode
		   ) {}

VOID
STDCALL
FatalExit(
	  int ExitCode
	  ) {}

VOID
STDCALL
RaiseException(
	       DWORD dwExceptionCode,
	       DWORD dwExceptionFlags,
	       DWORD nNumberOfArguments,
	       CONST DWORD *lpArguments
	       ) {}

LONG
STDCALL
UnhandledExceptionFilter(
			 struct _EXCEPTION_POINTERS *ExceptionInfo
			 ) {}

/* TODO: Should this go somewhere else? Colin Peters 1997/10/20 */
typedef LONG (*LPTOP_LEVEL_EXCEPTION_FILTER) (struct _EXCEPTION_POINTERS *);

LPTOP_LEVEL_EXCEPTION_FILTER
STDCALL
SetUnhandledExceptionFilter(
    LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter
    ) {}


HANDLE
STDCALL
CreateThread(
	     LPSECURITY_ATTRIBUTES lpThreadAttributes,
	     DWORD dwStackSize,
	     LPTHREAD_START_ROUTINE lpStartAddress,
	     LPVOID lpParameter,
	     DWORD dwCreationFlags,
	     LPDWORD lpThreadId
	     ) {}


HANDLE
STDCALL
CreateRemoteThread(
		   HANDLE hProcess,
		   LPSECURITY_ATTRIBUTES lpThreadAttributes,
		   DWORD dwStackSize,
		   LPTHREAD_START_ROUTINE lpStartAddress,
		   LPVOID lpParameter,
		   DWORD dwCreationFlags,
		   LPDWORD lpThreadId
		   ) {}


HANDLE
STDCALL
GetCurrentThread(
		 VOID
		 ) {}


DWORD
STDCALL
GetCurrentThreadId(
		   VOID
		   ) {}


DWORD
STDCALL
SetThreadAffinityMask(
		      HANDLE hThread,
		      DWORD dwThreadAffinityMask
		      ) {}


WINBOOL
STDCALL
SetThreadPriority(
		  HANDLE hThread,
		  int nPriority
		  ) {}


int
STDCALL
GetThreadPriority(
		  HANDLE hThread
		  ) {}


WINBOOL
STDCALL
GetThreadTimes(
	       HANDLE hThread,
	       LPFILETIME lpCreationTime,
	       LPFILETIME lpExitTime,
	       LPFILETIME lpKernelTime,
	       LPFILETIME lpUserTime
	       ) {}


VOID
STDCALL
ExitThread(
	   DWORD dwExitCode
	   ) {}


WINBOOL
STDCALL
TerminateThread(
		HANDLE hThread,
		DWORD dwExitCode
		) {}


WINBOOL
STDCALL
GetExitCodeThread(
		  HANDLE hThread,
		  LPDWORD lpExitCode
		  ) {}

WINBOOL
STDCALL
GetThreadSelectorEntry(
		       HANDLE hThread,
		       DWORD dwSelector,
		       LPLDT_ENTRY lpSelectorEntry
		       ) {}


DWORD
STDCALL
GetLastError(
	     VOID
	     ) {}


VOID
STDCALL
SetLastError(
	     DWORD dwErrCode
	     ) {}


WINBOOL
STDCALL
GetOverlappedResult(
		    HANDLE hFile,
		    LPOVERLAPPED lpOverlapped,
		    LPDWORD lpNumberOfBytesTransferred,
		    WINBOOL bWait
		    ) {}


HANDLE
STDCALL
CreateIoCompletionPort(
		       HANDLE FileHandle,
		       HANDLE ExistingCompletionPort,
		       DWORD CompletionKey,
		       DWORD NumberOfConcurrentThreads
		       ) {}


WINBOOL
STDCALL
GetQueuedCompletionStatus(
			  HANDLE CompletionPort,
			  LPDWORD lpNumberOfBytesTransferred,
			  LPDWORD lpCompletionKey,
			  LPOVERLAPPED *lpOverlapped,
			  DWORD dwMilliseconds
			  ) {}

UINT
STDCALL
SetErrorMode(
	     UINT uMode
	     ) {}


WINBOOL
STDCALL
ReadProcessMemory(
		  HANDLE hProcess,
		  LPCVOID lpBaseAddress,
		  LPVOID lpBuffer,
		  DWORD nSize,
		  LPDWORD lpNumberOfBytesRead
		  ) {}


WINBOOL
STDCALL
WriteProcessMemory(
		   HANDLE hProcess,
		   LPVOID lpBaseAddress,
		   LPVOID lpBuffer,
		   DWORD nSize,
		   LPDWORD lpNumberOfBytesWritten
		   ) {}


WINBOOL
STDCALL
GetThreadContext(
		 HANDLE hThread,
		 LPCONTEXT lpContext
		 ) {}


WINBOOL
STDCALL
SetThreadContext(
		 HANDLE hThread,
		 CONST CONTEXT *lpContext
		 ) {}


DWORD
STDCALL
SuspendThread(
	      HANDLE hThread
	      ) {}


DWORD
STDCALL
ResumeThread(
	     HANDLE hThread
	     ) {}


VOID
STDCALL
DebugBreak(
	   VOID
	   ) {}


WINBOOL
STDCALL
WaitForDebugEvent(
		  LPDEBUG_EVENT lpDebugEvent,
		  DWORD dwMilliseconds
		  ) {}


WINBOOL
STDCALL
ContinueDebugEvent(
		   DWORD dwProcessId,
		   DWORD dwThreadId,
		   DWORD dwContinueStatus
		   ) {}


WINBOOL
STDCALL
DebugActiveProcess(
		   DWORD dwProcessId
		   ) {}


VOID
STDCALL
InitializeCriticalSection(
			  LPCRITICAL_SECTION lpCriticalSection
			  ) {}


VOID
STDCALL
EnterCriticalSection(
		     LPCRITICAL_SECTION lpCriticalSection
		     ) {}


VOID
STDCALL
LeaveCriticalSection(
		     LPCRITICAL_SECTION lpCriticalSection
		     ) {}


VOID
STDCALL
DeleteCriticalSection(
		      LPCRITICAL_SECTION lpCriticalSection
		      ) {}


WINBOOL
STDCALL
SetEvent(
	 HANDLE hEvent
	 ) {}


WINBOOL
STDCALL
ResetEvent(
	   HANDLE hEvent
	   ) {}


WINBOOL
STDCALL
PulseEvent(
	   HANDLE hEvent
	   ) {}


WINBOOL
STDCALL
ReleaseSemaphore(
		 HANDLE hSemaphore,
		 LONG lReleaseCount,
		 LPLONG lpPreviousCount
		 ) {}


WINBOOL
STDCALL
ReleaseMutex(
	     HANDLE hMutex
	     ) {}


DWORD
STDCALL
WaitForSingleObject(
		    HANDLE hHandle,
		    DWORD dwMilliseconds
		    ) {}


DWORD
STDCALL
WaitForMultipleObjects(
		       DWORD nCount,
		       CONST HANDLE *lpHandles,
		       WINBOOL bWaitAll,
		       DWORD dwMilliseconds
		       ) {}


VOID
STDCALL
Sleep(
      DWORD dwMilliseconds
      ) {}


HGLOBAL
STDCALL
LoadResource(
	     HINSTANCE hModule,
	     HRSRC hResInfo
	     ) {}


DWORD
STDCALL
SizeofResource(
	       HINSTANCE hModule,
	       HRSRC hResInfo
	       ) {}



ATOM
STDCALL
GlobalDeleteAtom(
		 ATOM nAtom
		 ) {}


WINBOOL
STDCALL
InitAtomTable(
	      DWORD nSize
	      ) {}


ATOM
STDCALL
DeleteAtom(
	   ATOM nAtom
	   ) {}


UINT
STDCALL
SetHandleCount(
	       UINT uNumber
	       ) {}


DWORD
STDCALL
GetLogicalDrives(
		 VOID
		 ) {}


WINBOOL
STDCALL
LockFile(
	 HANDLE hFile,
	 DWORD dwFileOffsetLow,
	 DWORD dwFileOffsetHigh,
	 DWORD nNumberOfBytesToLockLow,
	 DWORD nNumberOfBytesToLockHigh
	 ) {}


WINBOOL
STDCALL
UnlockFile(
	   HANDLE hFile,
	   DWORD dwFileOffsetLow,
	   DWORD dwFileOffsetHigh,
	   DWORD nNumberOfBytesToUnlockLow,
	   DWORD nNumberOfBytesToUnlockHigh
	   ) {}


WINBOOL
STDCALL
LockFileEx(
	   HANDLE hFile,
	   DWORD dwFlags,
	   DWORD dwReserved,
	   DWORD nNumberOfBytesToLockLow,
	   DWORD nNumberOfBytesToLockHigh,
	   LPOVERLAPPED lpOverlapped
	   ) {}

WINBOOL
STDCALL
UnlockFileEx(
	     HANDLE hFile,
	     DWORD dwReserved,
	     DWORD nNumberOfBytesToUnlockLow,
	     DWORD nNumberOfBytesToUnlockHigh,
	     LPOVERLAPPED lpOverlapped
	     ) {}

WINBOOL
STDCALL
GetFileInformationByHandle(
			   HANDLE hFile,
			   LPBY_HANDLE_FILE_INFORMATION lpFileInformation
			   ) {}


DWORD
STDCALL
GetFileType(
	    HANDLE hFile
	    ) {}


DWORD
STDCALL
GetFileSize(
	    HANDLE hFile,
	    LPDWORD lpFileSizeHigh
	    ) {}


HANDLE
STDCALL
GetStdHandle(
	     DWORD nStdHandle
	     ) {}


WINBOOL
STDCALL
SetStdHandle(
	     DWORD nStdHandle,
	     HANDLE hHandle
	     ) {}


WINBOOL
STDCALL
WriteFile(
	  HANDLE hFile,
	  LPCVOID lpBuffer,
	  DWORD nNumberOfBytesToWrite,
	  LPDWORD lpNumberOfBytesWritten,
	  LPOVERLAPPED lpOverlapped
	  ) {}


WINBOOL
STDCALL
ReadFile(
	 HANDLE hFile,
	 LPVOID lpBuffer,
	 DWORD nNumberOfBytesToRead,
	 LPDWORD lpNumberOfBytesRead,
	 LPOVERLAPPED lpOverlapped
	 ) {}


WINBOOL
STDCALL
FlushFileBuffers(
		 HANDLE hFile
		 ) {}


WINBOOL
STDCALL
DeviceIoControl(
		HANDLE hDevice,
		DWORD dwIoControlCode,
		LPVOID lpInBuffer,
		DWORD nInBufferSize,
		LPVOID lpOutBuffer,
		DWORD nOutBufferSize,
		LPDWORD lpBytesReturned,
		LPOVERLAPPED lpOverlapped
		) {}


WINBOOL
STDCALL
SetEndOfFile(
	     HANDLE hFile
	     ) {}


DWORD
STDCALL
SetFilePointer(
	       HANDLE hFile,
	       LONG lDistanceToMove,
	       PLONG lpDistanceToMoveHigh,
	       DWORD dwMoveMethod
	       ) {}


WINBOOL
STDCALL
FindClose(
	  HANDLE hFindFile
	  ) {}


WINBOOL
STDCALL
GetFileTime(
	    HANDLE hFile,
	    LPFILETIME lpCreationTime,
	    LPFILETIME lpLastAccessTime,
	    LPFILETIME lpLastWriteTime
	    ) {}


WINBOOL
STDCALL
SetFileTime(
	    HANDLE hFile,
	    CONST FILETIME *lpCreationTime,
	    CONST FILETIME *lpLastAccessTime,
	    CONST FILETIME *lpLastWriteTime
	    ) {}


WINBOOL
STDCALL
CloseHandle(
	    HANDLE hObject
	    ) {}


WINBOOL
STDCALL
DuplicateHandle(
		HANDLE hSourceProcessHandle,
		HANDLE hSourceHandle,
		HANDLE hTargetProcessHandle,
		LPHANDLE lpTargetHandle,
		DWORD dwDesiredAccess,
		WINBOOL bInheritHandle,
		DWORD dwOptions
		) {}


WINBOOL
STDCALL
GetHandleInformation(
		     HANDLE hObject,
		     LPDWORD lpdwFlags
		     ) {}


WINBOOL
STDCALL
SetHandleInformation(
		     HANDLE hObject,
		     DWORD dwMask,
		     DWORD dwFlags
		     ) {}

DWORD
STDCALL
LoadModule(
	   LPCSTR lpModuleName,
	   LPVOID lpParameterBlock
	   ) {}


UINT
STDCALL
WinExec(
	LPCSTR lpCmdLine,
	UINT uCmdShow
	) {}


WINBOOL
STDCALL
ClearCommBreak(
	       HANDLE hFile
	       ) {}


WINBOOL
STDCALL
ClearCommError(
	       HANDLE hFile,
	       LPDWORD lpErrors,
	       LPCOMSTAT lpStat
	       ) {}


WINBOOL
STDCALL
SetupComm(
	  HANDLE hFile,
	  DWORD dwInQueue,
	  DWORD dwOutQueue
	  ) {}


WINBOOL
STDCALL
EscapeCommFunction(
		   HANDLE hFile,
		   DWORD dwFunc
		   ) {}


WINBOOL
STDCALL
GetCommConfig(
	      HANDLE hCommDev,
	      LPCOMMCONFIG lpCC,
	      LPDWORD lpdwSize
	      ) {}


WINBOOL
STDCALL
GetCommMask(
	    HANDLE hFile,
	    LPDWORD lpEvtMask
	    ) {}


WINBOOL
STDCALL
GetCommProperties(
		  HANDLE hFile,
		  LPCOMMPROP lpCommProp
		  ) {}


WINBOOL
STDCALL
GetCommModemStatus(
		   HANDLE hFile,
		   LPDWORD lpModemStat
		   ) {}


WINBOOL
STDCALL
GetCommState(
	     HANDLE hFile,
	     LPDCB lpDCB
	     ) {}


WINBOOL
STDCALL
GetCommTimeouts(
		HANDLE hFile,
		LPCOMMTIMEOUTS lpCommTimeouts
		) {}


WINBOOL
STDCALL
PurgeComm(
	  HANDLE hFile,
	  DWORD dwFlags
	  ) {}


WINBOOL
STDCALL
SetCommBreak(
	     HANDLE hFile
	     ) {}


WINBOOL
STDCALL
SetCommConfig(
	      HANDLE hCommDev,
	      LPCOMMCONFIG lpCC,
	      DWORD dwSize
	      ) {}


WINBOOL
STDCALL
SetCommMask(
	    HANDLE hFile,
	    DWORD dwEvtMask
	    ) {}


WINBOOL
STDCALL
SetCommState(
	     HANDLE hFile,
	     LPDCB lpDCB
	     ) {}


WINBOOL
STDCALL
SetCommTimeouts(
		HANDLE hFile,
		LPCOMMTIMEOUTS lpCommTimeouts
		) {}


WINBOOL
STDCALL
TransmitCommChar(
		 HANDLE hFile,
		 char cChar
		 ) {}


WINBOOL
STDCALL
WaitCommEvent(
	      HANDLE hFile,
	      LPDWORD lpEvtMask,
	      LPOVERLAPPED lpOverlapped
	      ) {}



DWORD
STDCALL
SetTapePosition(
		HANDLE hDevice,
		DWORD dwPositionMethod,
		DWORD dwPartition,
		DWORD dwOffsetLow,
		DWORD dwOffsetHigh,
		WINBOOL bImmediate
		) {}


DWORD
STDCALL
GetTapePosition(
		HANDLE hDevice,
		DWORD dwPositionType,
		LPDWORD lpdwPartition,
		LPDWORD lpdwOffsetLow,
		LPDWORD lpdwOffsetHigh
		) {}


DWORD
STDCALL
PrepareTape(
	    HANDLE hDevice,
	    DWORD dwOperation,
	    WINBOOL bImmediate
	    ) {}


DWORD
STDCALL
EraseTape(
	  HANDLE hDevice,
	  DWORD dwEraseType,
	  WINBOOL bImmediate
	  ) {}


DWORD
STDCALL
CreateTapePartition(
		    HANDLE hDevice,
		    DWORD dwPartitionMethod,
		    DWORD dwCount,
		    DWORD dwSize
		    ) {}


DWORD
STDCALL
WriteTapemark(
	      HANDLE hDevice,
	      DWORD dwTapemarkType,
	      DWORD dwTapemarkCount,
	      WINBOOL bImmediate
	      ) {}


DWORD
STDCALL
GetTapeStatus(
	      HANDLE hDevice
	      ) {}


DWORD
STDCALL
GetTapeParameters(
		  HANDLE hDevice,
		  DWORD dwOperation,
		  LPDWORD lpdwSize,
		  LPVOID lpTapeInformation
		  ) {}

DWORD
STDCALL
SetTapeParameters(
		  HANDLE hDevice,
		  DWORD dwOperation,
		  LPVOID lpTapeInformation
		  ) {}

WINBOOL
STDCALL
Beep(
     DWORD dwFreq,
     DWORD dwDuration
     ) {}


VOID
STDCALL
OpenSound(
	  VOID
	  ) {}


VOID
STDCALL
CloseSound(
	   VOID
	   ) {}


VOID
STDCALL
StartSound(
	   VOID
	   ) {}


VOID
STDCALL
StopSound(
	  VOID
	  ) {}


DWORD
STDCALL
WaitSoundState(
	       DWORD nState
	       ) {}


DWORD
STDCALL
SyncAllVoices(
	      VOID
	      ) {}


DWORD
STDCALL
CountVoiceNotes(
		DWORD nVoice
		) {}


LPDWORD
STDCALL
GetThresholdEvent(
		  VOID
		  ) {}


DWORD
STDCALL
GetThresholdStatus(
		   VOID
		   ) {}


DWORD
STDCALL
SetSoundNoise(
	      DWORD nSource,
	      DWORD nDuration
	      ) {}


DWORD
STDCALL
SetVoiceAccent(
	       DWORD nVoice,
	       DWORD nTempo,
	       DWORD nVolume,
	       DWORD nMode,
	       DWORD nPitch
	       ) {}


DWORD
STDCALL
SetVoiceEnvelope(
		 DWORD nVoice,
		 DWORD nShape,
		 DWORD nRepeat
		 ) {}


DWORD
STDCALL
SetVoiceNote(
	     DWORD nVoice,
	     DWORD nValue,
	     DWORD nLength,
	     DWORD nCdots
	     ) {}


DWORD
STDCALL
SetVoiceQueueSize(
		  DWORD nVoice,
		  DWORD nBytes
		  ) {}


DWORD
STDCALL
SetVoiceSound(
	      DWORD nVoice,
	      DWORD Frequency,
	      DWORD nDuration
	      ) {}


DWORD
STDCALL
SetVoiceThreshold(
		  DWORD nVoice,
		  DWORD nNotes
		  ) {}


int
STDCALL
MulDiv(
       int nNumber,
       int nNumerator,
       int nDenominator
       ) {}


VOID
STDCALL
GetSystemTime(
	      LPSYSTEMTIME lpSystemTime
	      ) {}


WINBOOL
STDCALL
SetSystemTime(
	      CONST SYSTEMTIME *lpSystemTime
	      ) {}


VOID
STDCALL
GetLocalTime(
	     LPSYSTEMTIME lpSystemTime
	     ) {}


WINBOOL
STDCALL
SetLocalTime(
	     CONST SYSTEMTIME *lpSystemTime
	     ) {}


VOID
STDCALL
GetSystemInfo(
	      LPSYSTEM_INFO lpSystemInfo
	      ) {}

WINBOOL
STDCALL
SystemTimeToTzSpecificLocalTime(
				LPTIME_ZONE_INFORMATION lpTimeZoneInformation,
				LPSYSTEMTIME lpUniversalTime,
				LPSYSTEMTIME lpLocalTime
				) {}


DWORD
STDCALL
GetTimeZoneInformation(
		       LPTIME_ZONE_INFORMATION lpTimeZoneInformation
		       ) {}


WINBOOL
STDCALL
SetTimeZoneInformation(
		       CONST TIME_ZONE_INFORMATION *lpTimeZoneInformation
		       ) {}

WINBOOL
STDCALL
SystemTimeToFileTime(
		     CONST SYSTEMTIME *lpSystemTime,
		     LPFILETIME lpFileTime
		     ) {}


WINBOOL
STDCALL
FileTimeToLocalFileTime(
			CONST FILETIME *lpFileTime,
			LPFILETIME lpLocalFileTime
			) {}


WINBOOL
STDCALL
LocalFileTimeToFileTime(
			CONST FILETIME *lpLocalFileTime,
			LPFILETIME lpFileTime
			) {}


WINBOOL
STDCALL
FileTimeToSystemTime(
		     CONST FILETIME *lpFileTime,
		     LPSYSTEMTIME lpSystemTime
		     ) {}


LONG
STDCALL
CompareFileTime(
		CONST FILETIME *lpFileTime1,
		CONST FILETIME *lpFileTime2
		) {}


WINBOOL
STDCALL
FileTimeToDosDateTime(
		      CONST FILETIME *lpFileTime,
		      LPWORD lpFatDate,
		      LPWORD lpFatTime
		      ) {}


WINBOOL
STDCALL
DosDateTimeToFileTime(
		      WORD wFatDate,
		      WORD wFatTime,
		      LPFILETIME lpFileTime
		      ) {}


DWORD
STDCALL
GetTickCount(
	     VOID
	     ) {}


WINBOOL
STDCALL
SetSystemTimeAdjustment(
			DWORD dwTimeAdjustment,
			WINBOOL  bTimeAdjustmentDisabled
			) {}


WINBOOL
STDCALL
GetSystemTimeAdjustment(
			PDWORD lpTimeAdjustment,
			PDWORD lpTimeIncrement,
			PWINBOOL  lpTimeAdjustmentDisabled
			) {}


WINBOOL
STDCALL
CreatePipe(
	   PHANDLE hReadPipe,
	   PHANDLE hWritePipe,
	   LPSECURITY_ATTRIBUTES lpPipeAttributes,
	   DWORD nSize
	   ) {}


WINBOOL
STDCALL
ConnectNamedPipe(
		 HANDLE hNamedPipe,
		 LPOVERLAPPED lpOverlapped
		 ) {}


WINBOOL
STDCALL
DisconnectNamedPipe(
		    HANDLE hNamedPipe
		    ) {}


WINBOOL
STDCALL
SetNamedPipeHandleState(
			HANDLE hNamedPipe,
			LPDWORD lpMode,
			LPDWORD lpMaxCollectionCount,
			LPDWORD lpCollectDataTimeout
			) {}


WINBOOL
STDCALL
GetNamedPipeInfo(
		 HANDLE hNamedPipe,
		 LPDWORD lpFlags,
		 LPDWORD lpOutBufferSize,
		 LPDWORD lpInBufferSize,
		 LPDWORD lpMaxInstances
		 ) {}


WINBOOL
STDCALL
PeekNamedPipe(
	      HANDLE hNamedPipe,
	      LPVOID lpBuffer,
	      DWORD nBufferSize,
	      LPDWORD lpBytesRead,
	      LPDWORD lpTotalBytesAvail,
	      LPDWORD lpBytesLeftThisMessage
	      ) {}


WINBOOL
STDCALL
TransactNamedPipe(
		  HANDLE hNamedPipe,
		  LPVOID lpInBuffer,
		  DWORD nInBufferSize,
		  LPVOID lpOutBuffer,
		  DWORD nOutBufferSize,
		  LPDWORD lpBytesRead,
		  LPOVERLAPPED lpOverlapped
		  ) {}



WINBOOL
STDCALL
GetMailslotInfo(
		HANDLE hMailslot,
		LPDWORD lpMaxMessageSize,
		LPDWORD lpNextSize,
		LPDWORD lpMessageCount,
		LPDWORD lpReadTimeout
		) {}


WINBOOL
STDCALL
SetMailslotInfo(
		HANDLE hMailslot,
		DWORD lReadTimeout
		) {}


LPVOID
STDCALL
MapViewOfFile(
	      HANDLE hFileMappingObject,
	      DWORD dwDesiredAccess,
	      DWORD dwFileOffsetHigh,
	      DWORD dwFileOffsetLow,
	      DWORD dwNumberOfBytesToMap
	      ) {}


WINBOOL
STDCALL
FlushViewOfFile(
		LPCVOID lpBaseAddress,
		DWORD dwNumberOfBytesToFlush
		) {}


WINBOOL
STDCALL
UnmapViewOfFile(
		LPVOID lpBaseAddress
		) {}

HFILE
STDCALL
OpenFile(
	 LPCSTR lpFileName,
	 LPOFSTRUCT lpReOpenBuff,
	 UINT uStyle
	 ) {}


HFILE
STDCALL
_lopen(
       LPCSTR lpPathName,
       int iReadWrite
       ) {}


HFILE
STDCALL
_lcreat(
	LPCSTR lpPathName,
	int  iAttribute
	) {}


UINT
STDCALL
_lread(
       HFILE hFile,
       LPVOID lpBuffer,
       UINT uBytes
       ) {}


UINT
STDCALL
_lwrite(
	HFILE hFile,
	LPCSTR lpBuffer,
	UINT uBytes
	) {}


long
STDCALL
_hread(
       HFILE hFile,
       LPVOID lpBuffer,
       long lBytes
       ) {}


long
STDCALL
_hwrite(
	HFILE hFile,
	LPCSTR lpBuffer,
	long lBytes
	) {}


HFILE
STDCALL
_lclose(
	HFILE hFile
	) {}


LONG
STDCALL
_llseek(
	HFILE hFile,
	LONG lOffset,
	int iOrigin
	) {}


WINBOOL
STDCALL
IsTextUnicode(
	      CONST LPVOID lpBuffer,
	      int cb,
	      LPINT lpi
	      ) {}


DWORD
STDCALL
TlsAlloc(
	 VOID
	 ) {}

LPVOID
STDCALL
TlsGetValue(
	    DWORD dwTlsIndex
	    ) {}


WINBOOL
STDCALL
TlsSetValue(
	    DWORD dwTlsIndex,
	    LPVOID lpTlsValue
	    ) {}


WINBOOL
STDCALL
TlsFree(
	DWORD dwTlsIndex
	) {}

DWORD
STDCALL
SleepEx(
	DWORD dwMilliseconds,
	WINBOOL bAlertable
	) {}


DWORD
STDCALL
WaitForSingleObjectEx(
		      HANDLE hHandle,
		      DWORD dwMilliseconds,
		      WINBOOL bAlertable
		      ) {}


DWORD
STDCALL
WaitForMultipleObjectsEx(
			 DWORD nCount,
			 CONST HANDLE *lpHandles,
			 WINBOOL bWaitAll,
			 DWORD dwMilliseconds,
			 WINBOOL bAlertable
			 ) {}


WINBOOL
STDCALL
ReadFileEx(
	   HANDLE hFile,
	   LPVOID lpBuffer,
	   DWORD nNumberOfBytesToRead,
	   LPOVERLAPPED lpOverlapped,
	   LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
	   ) {}


WINBOOL
STDCALL
WriteFileEx(
	    HANDLE hFile,
	    LPCVOID lpBuffer,
	    DWORD nNumberOfBytesToWrite,
	    LPOVERLAPPED lpOverlapped,
	    LPOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
	    ) {}


WINBOOL
STDCALL
BackupRead(
	   HANDLE hFile,
	   LPBYTE lpBuffer,
	   DWORD nNumberOfBytesToRead,
	   LPDWORD lpNumberOfBytesRead,
	   WINBOOL bAbort,
	   WINBOOL bProcessSecurity,
	   LPVOID *lpContext
	   ) {}


WINBOOL
STDCALL
BackupSeek(
	   HANDLE hFile,
	   DWORD  dwLowBytesToSeek,
	   DWORD  dwHighBytesToSeek,
	   LPDWORD lpdwLowByteSeeked,
	   LPDWORD lpdwHighByteSeeked,
	   LPVOID *lpContext
	   ) {}


WINBOOL
STDCALL
BackupWrite(
	    HANDLE hFile,
	    LPBYTE lpBuffer,
	    DWORD nNumberOfBytesToWrite,
	    LPDWORD lpNumberOfBytesWritten,
	    WINBOOL bAbort,
	    WINBOOL bProcessSecurity,
	    LPVOID *lpContext
	    ) {}

WINBOOL
STDCALL
SetProcessShutdownParameters(
			     DWORD dwLevel,
			     DWORD dwFlags
			     ) {}


WINBOOL
STDCALL
GetProcessShutdownParameters(
			     LPDWORD lpdwLevel,
			     LPDWORD lpdwFlags
			     ) {}


VOID
STDCALL
SetFileApisToOEM( VOID ) {}


VOID
STDCALL
SetFileApisToANSI( VOID ) {}


WINBOOL
STDCALL
AreFileApisANSI( VOID ) {}

WINBOOL
STDCALL
CloseEventLog (
	       HANDLE hEventLog
		) {}


WINBOOL
STDCALL
DeregisterEventSource (
		       HANDLE hEventLog
			) {}


WINBOOL
STDCALL
NotifyChangeEventLog (
		      HANDLE hEventLog,
		      HANDLE hEvent
		       ) {}


WINBOOL
STDCALL
GetNumberOfEventLogRecords (
			    HANDLE hEventLog,
			    PDWORD NumberOfRecords
			     ) {}


WINBOOL
STDCALL
GetOldestEventLogRecord (
			 HANDLE hEventLog,
			 PDWORD OldestRecord
			  ) {}

WINBOOL
STDCALL
DuplicateToken(
	       HANDLE ExistingTokenHandle,
	       SECURITY_IMPERSONATION_LEVEL ImpersonationLevel,
	       PHANDLE DuplicateTokenHandle
	       ) {}


WINBOOL
STDCALL
GetKernelObjectSecurity (
			 HANDLE Handle,
			 SECURITY_INFORMATION RequestedInformation,
			 PSECURITY_DESCRIPTOR pSecurityDescriptor,
			 DWORD nLength,
			 LPDWORD lpnLengthNeeded
			  ) {}


WINBOOL
STDCALL
ImpersonateNamedPipeClient(
			   HANDLE hNamedPipe
			   ) {}


WINBOOL
STDCALL
ImpersonateLoggedOnUser(
			   HANDLE hToken
			   ) {}


WINBOOL
STDCALL
ImpersonateSelf(
		SECURITY_IMPERSONATION_LEVEL ImpersonationLevel
		) {}


WINBOOL
STDCALL
RevertToSelf (
	      VOID
	       ) {}


WINBOOL
STDCALL
SetThreadToken (
		PHANDLE Thread,
		HANDLE Token
		 ) {}


WINBOOL
STDCALL
AccessCheck (
	     PSECURITY_DESCRIPTOR pSecurityDescriptor,
	     HANDLE ClientToken,
	     DWORD DesiredAccess,
	     PGENERIC_MAPPING GenericMapping,
	     PPRIVILEGE_SET PrivilegeSet,
	     LPDWORD PrivilegeSetLength,
	     LPDWORD GrantedAccess,
	     LPBOOL AccessStatus
	      ) {}



WINBOOL
STDCALL
OpenProcessToken (
		  HANDLE ProcessHandle,
		  DWORD DesiredAccess,
		  PHANDLE TokenHandle
		   ) {}



WINBOOL
STDCALL
OpenThreadToken (
		 HANDLE ThreadHandle,
		 DWORD DesiredAccess,
		 WINBOOL OpenAsSelf,
		 PHANDLE TokenHandle
		  ) {}



WINBOOL
STDCALL
GetTokenInformation (
		     HANDLE TokenHandle,
		     TOKEN_INFORMATION_CLASS TokenInformationClass,
		     LPVOID TokenInformation,
		     DWORD TokenInformationLength,
		     PDWORD ReturnLength
		      ) {}



WINBOOL
STDCALL
SetTokenInformation (
		     HANDLE TokenHandle,
		     TOKEN_INFORMATION_CLASS TokenInformationClass,
		     LPVOID TokenInformation,
		     DWORD TokenInformationLength
		      ) {}



WINBOOL
STDCALL
AdjustTokenPrivileges (
		       HANDLE TokenHandle,
		       WINBOOL DisableAllPrivileges,
		       PTOKEN_PRIVILEGES NewState,
		       DWORD BufferLength,
		       PTOKEN_PRIVILEGES PreviousState,
		       PDWORD ReturnLength
			) {}



WINBOOL
STDCALL
AdjustTokenGroups (
		   HANDLE TokenHandle,
		   WINBOOL ResetToDefault,
		   PTOKEN_GROUPS NewState,
		   DWORD BufferLength,
		   PTOKEN_GROUPS PreviousState,
		   PDWORD ReturnLength
		    ) {}



WINBOOL
STDCALL
PrivilegeCheck (
		HANDLE ClientToken,
		PPRIVILEGE_SET RequiredPrivileges,
		LPBOOL pfResult
		 ) {}



WINBOOL
STDCALL
IsValidSid (
	    PSID pSid
	     ) {}



WINBOOL
STDCALL
EqualSid (
	  PSID pSid1,
	  PSID pSid2
	   ) {}



WINBOOL
STDCALL
EqualPrefixSid (
		PSID pSid1,
		PSID pSid2
		 ) {}



DWORD
STDCALL
GetSidLengthRequired (
		      UCHAR nSubAuthorityCount
		       ) {}



WINBOOL
STDCALL
AllocateAndInitializeSid (
			  PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority,
			  BYTE nSubAuthorityCount,
			  DWORD nSubAuthority0,
			  DWORD nSubAuthority1,
			  DWORD nSubAuthority2,
			  DWORD nSubAuthority3,
			  DWORD nSubAuthority4,
			  DWORD nSubAuthority5,
			  DWORD nSubAuthority6,
			  DWORD nSubAuthority7,
			  PSID *pSid
			   ) {}


PVOID
STDCALL
FreeSid(
	PSID pSid
	) {}


WINBOOL
STDCALL
InitializeSid (
	       PSID Sid,
	       PSID_IDENTIFIER_AUTHORITY pIdentifierAuthority,
	       BYTE nSubAuthorityCount
		) {}



PSID_IDENTIFIER_AUTHORITY
STDCALL
GetSidIdentifierAuthority (
			   PSID pSid
			    ) {}



PDWORD
STDCALL
GetSidSubAuthority (
		    PSID pSid,
		    DWORD nSubAuthority
		     ) {}



PUCHAR
STDCALL
GetSidSubAuthorityCount (
			 PSID pSid
			  ) {}



DWORD
STDCALL
GetLengthSid (
	      PSID pSid
	       ) {}



WINBOOL
STDCALL
CopySid (
	 DWORD nDestinationSidLength,
	 PSID pDestinationSid,
	 PSID pSourceSid
	  ) {}



WINBOOL
STDCALL
AreAllAccessesGranted (
		       DWORD GrantedAccess,
		       DWORD DesiredAccess
			) {}



WINBOOL
STDCALL
AreAnyAccessesGranted (
		       DWORD GrantedAccess,
		       DWORD DesiredAccess
			) {}



VOID
STDCALL
MapGenericMask (
		PDWORD AccessMask,
		PGENERIC_MAPPING GenericMapping
		 ) {}



WINBOOL
STDCALL
IsValidAcl (
	    PACL pAcl
	     ) {}



WINBOOL
STDCALL
InitializeAcl (
	       PACL pAcl,
	       DWORD nAclLength,
	       DWORD dwAclRevision
		) {}



WINBOOL
STDCALL
GetAclInformation (
		   PACL pAcl,
		   LPVOID pAclInformation,
		   DWORD nAclInformationLength,
		   ACL_INFORMATION_CLASS dwAclInformationClass
		    ) {}



WINBOOL
STDCALL
SetAclInformation (
		   PACL pAcl,
		   LPVOID pAclInformation,
		   DWORD nAclInformationLength,
		   ACL_INFORMATION_CLASS dwAclInformationClass
		    ) {}



WINBOOL
STDCALL
AddAce (
	PACL pAcl,
	DWORD dwAceRevision,
	DWORD dwStartingAceIndex,
	LPVOID pAceList,
	DWORD nAceListLength
	 ) {}



WINBOOL
STDCALL
DeleteAce (
	   PACL pAcl,
	   DWORD dwAceIndex
	    ) {}



WINBOOL
STDCALL
GetAce (
	PACL pAcl,
	DWORD dwAceIndex,
	LPVOID *pAce
	 ) {}



WINBOOL
STDCALL
AddAccessAllowedAce (
		     PACL pAcl,
		     DWORD dwAceRevision,
		     DWORD AccessMask,
		     PSID pSid
		      ) {}



WINBOOL
STDCALL
AddAccessDeniedAce (
		    PACL pAcl,
		    DWORD dwAceRevision,
		    DWORD AccessMask,
		    PSID pSid
		     ) {}



WINBOOL
STDCALL
AddAuditAccessAce(
		  PACL pAcl,
		  DWORD dwAceRevision,
		  DWORD dwAccessMask,
		  PSID pSid,
		  WINBOOL bAuditSuccess,
		  WINBOOL bAuditFailure
		  ) {}



WINBOOL
STDCALL
FindFirstFreeAce (
		  PACL pAcl,
		  LPVOID *pAce
		   ) {}



WINBOOL
STDCALL
InitializeSecurityDescriptor (
			      PSECURITY_DESCRIPTOR pSecurityDescriptor,
			      DWORD dwRevision
			       ) {}



WINBOOL
STDCALL
IsValidSecurityDescriptor (
			   PSECURITY_DESCRIPTOR pSecurityDescriptor
			    ) {}



DWORD
STDCALL
GetSecurityDescriptorLength (
			     PSECURITY_DESCRIPTOR pSecurityDescriptor
			      ) {}



WINBOOL
STDCALL
GetSecurityDescriptorControl (
			      PSECURITY_DESCRIPTOR pSecurityDescriptor,
			      PSECURITY_DESCRIPTOR_CONTROL pControl,
			      LPDWORD lpdwRevision
			       ) {}



WINBOOL
STDCALL
SetSecurityDescriptorDacl (
			   PSECURITY_DESCRIPTOR pSecurityDescriptor,
			   WINBOOL bDaclPresent,
			   PACL pDacl,
			   WINBOOL bDaclDefaulted
			    ) {}



WINBOOL
STDCALL
GetSecurityDescriptorDacl (
			   PSECURITY_DESCRIPTOR pSecurityDescriptor,
			   LPBOOL lpbDaclPresent,
			   PACL *pDacl,
			   LPBOOL lpbDaclDefaulted
			    ) {}



WINBOOL
STDCALL
SetSecurityDescriptorSacl (
			   PSECURITY_DESCRIPTOR pSecurityDescriptor,
			   WINBOOL bSaclPresent,
			   PACL pSacl,
			   WINBOOL bSaclDefaulted
			    ) {}



WINBOOL
STDCALL
GetSecurityDescriptorSacl (
			   PSECURITY_DESCRIPTOR pSecurityDescriptor,
			   LPBOOL lpbSaclPresent,
			   PACL *pSacl,
			   LPBOOL lpbSaclDefaulted
			    ) {}



WINBOOL
STDCALL
SetSecurityDescriptorOwner (
			    PSECURITY_DESCRIPTOR pSecurityDescriptor,
			    PSID pOwner,
			    WINBOOL bOwnerDefaulted
			     ) {}



WINBOOL
STDCALL
GetSecurityDescriptorOwner (
			    PSECURITY_DESCRIPTOR pSecurityDescriptor,
			    PSID *pOwner,
			    LPBOOL lpbOwnerDefaulted
			     ) {}



WINBOOL
STDCALL
SetSecurityDescriptorGroup (
			    PSECURITY_DESCRIPTOR pSecurityDescriptor,
			    PSID pGroup,
			    WINBOOL bGroupDefaulted
			     ) {}



WINBOOL
STDCALL
GetSecurityDescriptorGroup (
			    PSECURITY_DESCRIPTOR pSecurityDescriptor,
			    PSID *pGroup,
			    LPBOOL lpbGroupDefaulted
			     ) {}



WINBOOL
STDCALL
CreatePrivateObjectSecurity (
			     PSECURITY_DESCRIPTOR ParentDescriptor,
			     PSECURITY_DESCRIPTOR CreatorDescriptor,
			     PSECURITY_DESCRIPTOR * NewDescriptor,
			     WINBOOL IsDirectoryObject,
			     HANDLE Token,
			     PGENERIC_MAPPING GenericMapping
			      ) {}



WINBOOL
STDCALL
SetPrivateObjectSecurity (
			  SECURITY_INFORMATION SecurityInformation,
			  PSECURITY_DESCRIPTOR ModificationDescriptor,
			  PSECURITY_DESCRIPTOR *ObjectsSecurityDescriptor,
			  PGENERIC_MAPPING GenericMapping,
			  HANDLE Token
			   ) {}



WINBOOL
STDCALL
GetPrivateObjectSecurity (
			  PSECURITY_DESCRIPTOR ObjectDescriptor,
			  SECURITY_INFORMATION SecurityInformation,
			  PSECURITY_DESCRIPTOR ResultantDescriptor,
			  DWORD DescriptorLength,
			  PDWORD ReturnLength
			   ) {}



WINBOOL
STDCALL
DestroyPrivateObjectSecurity (
			      PSECURITY_DESCRIPTOR * ObjectDescriptor
			       ) {}



WINBOOL
STDCALL
MakeSelfRelativeSD (
		    PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor,
		    PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor,
		    LPDWORD lpdwBufferLength
		     ) {}



WINBOOL
STDCALL
MakeAbsoluteSD (
		PSECURITY_DESCRIPTOR pSelfRelativeSecurityDescriptor,
		PSECURITY_DESCRIPTOR pAbsoluteSecurityDescriptor,
		LPDWORD lpdwAbsoluteSecurityDescriptorSize,
		PACL pDacl,
		LPDWORD lpdwDaclSize,
		PACL pSacl,
		LPDWORD lpdwSaclSize,
		PSID pOwner,
		LPDWORD lpdwOwnerSize,
		PSID pPrimaryGroup,
		LPDWORD lpdwPrimaryGroupSize
		 ) {}



WINBOOL
STDCALL
SetKernelObjectSecurity (
			 HANDLE Handle,
			 SECURITY_INFORMATION SecurityInformation,
			 PSECURITY_DESCRIPTOR SecurityDescriptor
			  ) {}


WINBOOL
STDCALL
FindNextChangeNotification(
			   HANDLE hChangeHandle
			   ) {}


WINBOOL
STDCALL
FindCloseChangeNotification(
			    HANDLE hChangeHandle
			    ) {}


WINBOOL
STDCALL
VirtualLock(
	    LPVOID lpAddress,
	    DWORD dwSize
	    ) {}


WINBOOL
STDCALL
VirtualUnlock(
	      LPVOID lpAddress,
	      DWORD dwSize
	      ) {}


LPVOID
STDCALL
MapViewOfFileEx(
		HANDLE hFileMappingObject,
		DWORD dwDesiredAccess,
		DWORD dwFileOffsetHigh,
		DWORD dwFileOffsetLow,
		DWORD dwNumberOfBytesToMap,
		LPVOID lpBaseAddress
		) {}


WINBOOL
STDCALL
SetPriorityClass(
		 HANDLE hProcess,
		 DWORD dwPriorityClass
		 ) {}


DWORD
STDCALL
GetPriorityClass(
		 HANDLE hProcess
		 ) {}


WINBOOL
STDCALL
IsBadReadPtr(
	     CONST VOID *lp,
	     UINT ucb
	     ) {}


WINBOOL
STDCALL
IsBadWritePtr(
	      LPVOID lp,
	      UINT ucb
	      ) {}


WINBOOL
STDCALL
IsBadHugeReadPtr(
		 CONST VOID *lp,
		 UINT ucb
		 ) {}


WINBOOL
STDCALL
IsBadHugeWritePtr(
		  LPVOID lp,
		  UINT ucb
		  ) {}


WINBOOL
STDCALL
IsBadCodePtr(
	     FARPROC lpfn
	     ) {}

WINBOOL
STDCALL
AllocateLocallyUniqueId(
			PLUID Luid
			) {}


WINBOOL
STDCALL
QueryPerformanceCounter(
			LARGE_INTEGER *lpPerformanceCount
			) {}


WINBOOL
STDCALL
QueryPerformanceFrequency(
			  LARGE_INTEGER *lpFrequency
			  ) {}

VOID
STDCALL
MoveMemory (
	    PVOID Destination,
	    CONST VOID *Source,
	    DWORD Length
	     ) {}

VOID
STDCALL
FillMemory (
	    PVOID Destination,
	    DWORD Length,
	    BYTE  Fill
	     ) {}

VOID
STDCALL
ZeroMemory (
	    PVOID Destination,
	    DWORD Length
	     ) {}

VOID
STDCALL
CopyMemory (
	    PVOID Destination,
	    CONST VOID *Source,
	    DWORD Length
	     ) {}

/* The memory functions don't seem to be defined in the libraries, so
   define macro versions as well.  */
#define MoveMemory(t, s, c) memmove ((t), (s), (c))
#define FillMemory(p, c, v) memset ((p), (v), (c))
#define ZeroMemory(p, c) memset ((p), 0, (c))
#define CopyMemory(t, s, c) memcpy ((t), (s), (c))

#ifdef WIN95
HKL
STDCALL
ActivateKeyboardLayout(
		       HKL hkl,
		       UINT Flags) {}
#else
WINBOOL
STDCALL
ActivateKeyboardLayout(
		       HKL hkl,
		       UINT Flags) {}
#endif /* WIN95 */

 
int
STDCALL
ToUnicodeEx(
	    UINT wVirtKey,
	    UINT wScanCode,
	    PBYTE lpKeyState,
	    LPWSTR pwszBuff,
	    int cchBuff,
	    UINT wFlags,
	    HKL dwhkl) {}

 
WINBOOL
STDCALL
UnloadKeyboardLayout(
		     HKL hkl) {}

 
int
STDCALL
GetKeyboardLayoutList(
		      int nBuff,
		      HKL *lpList) {}

 
HKL
STDCALL
GetKeyboardLayout(
		  DWORD dwLayout
		  ) {}

 
HDESK
STDCALL
OpenInputDesktop(
		 DWORD dwFlags,
		 WINBOOL fInherit,
		 DWORD dwDesiredAccess) {}

WINBOOL
STDCALL
EnumDesktopWindows(
		   HDESK hDesktop,
		   ENUMWINDOWSPROC lpfn,
		   LPARAM lParam) {}

 
WINBOOL
STDCALL
SwitchDesktop(
	      HDESK hDesktop) {}

 
WINBOOL
STDCALL
SetThreadDesktop(
		 HDESK hDesktop) {}

 
WINBOOL
STDCALL
CloseDesktop(
	     HDESK hDesktop) {}

 
HDESK
STDCALL
GetThreadDesktop(
		 DWORD dwThreadId) {}

 
WINBOOL
STDCALL
CloseWindowStation(
		   HWINSTA hWinSta) {}

 
WINBOOL
STDCALL
SetProcessWindowStation(
			HWINSTA hWinSta) {}

 
HWINSTA
STDCALL
GetProcessWindowStation(
			VOID) {}

 
WINBOOL
STDCALL
SetUserObjectSecurity(
		      HANDLE hObj,
		      PSECURITY_INFORMATION pSIRequested,
		      PSECURITY_DESCRIPTOR pSID) {}

 
WINBOOL
STDCALL
GetUserObjectSecurity(
		      HANDLE hObj,
		      PSECURITY_INFORMATION pSIRequested,
		      PSECURITY_DESCRIPTOR pSID,
		      DWORD nLength,
		      LPDWORD lpnLengthNeeded) {}

 
WINBOOL
STDCALL
TranslateMessage(
		 CONST MSG *lpMsg) {}

WINBOOL
STDCALL
SetMessageQueue(
		int cMessagesMax) {}

WINBOOL
STDCALL
RegisterHotKey(
	       HWND hWnd ,
	       int anID,
	       UINT fsModifiers,
	       UINT vk) {}

 
WINBOOL
STDCALL
UnregisterHotKey(
		 HWND hWnd,
		 int anID) {}

 
WINBOOL
STDCALL
ExitWindowsEx(
	      UINT uFlags,
	      DWORD dwReserved) {}

 
WINBOOL
STDCALL
SwapMouseButton(
		WINBOOL fSwap) {}

 
DWORD
STDCALL
GetMessagePos(
	      VOID) {}

 
LONG
STDCALL
GetMessageTime(
	       VOID) {}

 
LONG
STDCALL
GetMessageExtraInfo(
		    VOID) {}

 
LPARAM
STDCALL
SetMessageExtraInfo(
		    LPARAM lParam) {}

 
long  
STDCALL  
BroadcastSystemMessage(
		       DWORD d,
		       LPDWORD d1, 
		       UINT v,
		       WPARAM wParam, 
		       LPARAM lParam) {}

WINBOOL
STDCALL
AttachThreadInput(
		  DWORD idAttach,
		  DWORD idAttachTo,
		  WINBOOL fAttach) {}

 
WINBOOL
STDCALL
ReplyMessage(
	     LRESULT lResult) {}

 
WINBOOL
STDCALL
WaitMessage(
	    VOID) {}

 
DWORD
STDCALL
WaitForInputIdle(
		 HANDLE hProcess,
		 DWORD dwMilliseconds) {}

 
VOID
STDCALL
PostQuitMessage(
		int nExitCode) {}

WINBOOL
STDCALL
InSendMessage(
	      VOID) {}

 
UINT
STDCALL
GetDoubleClickTime(
		   VOID) {}

 
WINBOOL
STDCALL
SetDoubleClickTime(
		   UINT v) {}

 
WINBOOL
STDCALL
IsWindow(
	 HWND hWnd) {}

 
WINBOOL
STDCALL
IsMenu(
       HMENU hMenu) {}

 
WINBOOL
STDCALL
IsChild(
	HWND hWndParent,
	HWND hWnd) {}

 
WINBOOL
STDCALL
DestroyWindow(
	      HWND hWnd) {}

 
WINBOOL
STDCALL
ShowWindow(
	   HWND hWnd,
	   int nCmdShow) {}

 
WINBOOL
STDCALL
ShowWindowAsync(
		HWND hWnd,
		int nCmdShow) {}

 
WINBOOL
STDCALL
FlashWindow(
	    HWND hWnd,
	    WINBOOL bInvert) {}

 
WINBOOL
STDCALL
ShowOwnedPopups(
		HWND hWnd,
		WINBOOL fShow) {}

 
WINBOOL
STDCALL
OpenIcon(
	 HWND hWnd) {}

 
WINBOOL
STDCALL
CloseWindow(
	    HWND hWnd) {}

 
WINBOOL
STDCALL
MoveWindow(
	   HWND hWnd,
	   int X,
	   int Y,
	   int nWidth,
	   int nHeight,
	   WINBOOL bRepaint) {}

 
WINBOOL
STDCALL
SetWindowPos(
	     HWND hWnd,
	     HWND hWndInsertAfter ,
	     int X,
	     int Y,
	     int cx,
	     int cy,
	     UINT uFlags) {}

 
WINBOOL
STDCALL
GetWindowPlacement(
		   HWND hWnd,
		   WINDOWPLACEMENT *lpwndpl) {}

 
WINBOOL
STDCALL
SetWindowPlacement(
		   HWND hWnd,
		   CONST WINDOWPLACEMENT *lpwndpl) {}

 
HDWP
STDCALL
BeginDeferWindowPos(
		    int nNumWindows) {}

 
HDWP
STDCALL
DeferWindowPos(
	       HDWP hWinPosInfo,
	       HWND hWnd,
	       HWND hWndInsertAfter,
	       int x,
	       int y,
	       int cx,
	       int cy,
	       UINT uFlags) {}

 
WINBOOL
STDCALL
EndDeferWindowPos(
		  HDWP hWinPosInfo) {}

 
WINBOOL
STDCALL
IsWindowVisible(
		HWND hWnd) {}

 
WINBOOL
STDCALL
IsIconic(
	 HWND hWnd) {}

 
WINBOOL
STDCALL
AnyPopup(
	 VOID) {}

 
WINBOOL
STDCALL
BringWindowToTop(
		 HWND hWnd) {}

 
WINBOOL
STDCALL
IsZoomed(
	 HWND hWnd) {}

 
WINBOOL
STDCALL
EndDialog(
	  HWND hDlg,
	  int nResult) {}

 
HWND
STDCALL
GetDlgItem(
	   HWND hDlg,
	   int nIDDlgItem) {}

 
WINBOOL
STDCALL
SetDlgItemInt(
	      HWND hDlg,
	      int nIDDlgItem,
	      UINT uValue,
	      WINBOOL bSigned) {}

 
UINT
STDCALL
GetDlgItemInt(
	      HWND hDlg,
	      int nIDDlgItem,
	      WINBOOL *lpTranslated,
	      WINBOOL bSigned) {}

 
WINBOOL
STDCALL
CheckDlgButton(
	       HWND hDlg,
	       int nIDButton,
	       UINT uCheck) {}

 
WINBOOL
STDCALL
CheckRadioButton(
		 HWND hDlg,
		 int nIDFirstButton,
		 int nIDLastButton,
		 int nIDCheckButton) {}

 
UINT
STDCALL
IsDlgButtonChecked(
		   HWND hDlg,
		   int nIDButton) {}

 
HWND
STDCALL
GetNextDlgGroupItem(
		    HWND hDlg,
		    HWND hCtl,
		    WINBOOL bPrevious) {}

 
HWND
STDCALL
GetNextDlgTabItem(
		  HWND hDlg,
		  HWND hCtl,
		  WINBOOL bPrevious) {}

 
int
STDCALL
GetDlgCtrlID(
	     HWND hWnd) {}

 
long
STDCALL
GetDialogBaseUnits(VOID) {}

WINBOOL
STDCALL
OpenClipboard(
	      HWND hWndNewOwner) {}

 
WINBOOL
STDCALL
CloseClipboard(
	       VOID) {}

 
HWND
STDCALL
GetClipboardOwner(
		  VOID) {}

 
HWND
STDCALL
SetClipboardViewer(
		   HWND hWndNewViewer) {}

 
HWND
STDCALL
GetClipboardViewer(
		   VOID) {}

 
WINBOOL
STDCALL
ChangeClipboardChain(
		     HWND hWndRemove,
		     HWND hWndNewNext) {}

 
HANDLE
STDCALL
SetClipboardData(
		 UINT uFormat,
		 HANDLE hMem) {}

 
HANDLE
STDCALL
GetClipboardData(
		 UINT uFormat) {}

 
 
int
STDCALL
CountClipboardFormats(
		      VOID) {}

 
UINT
STDCALL
EnumClipboardFormats(
		     UINT format) {}

 
WINBOOL
STDCALL
EmptyClipboard(
	       VOID) {}

 
WINBOOL
STDCALL
IsClipboardFormatAvailable(
			   UINT format) {}

 
int
STDCALL
GetPriorityClipboardFormat(
			   UINT *paFormatPriorityList,
			   int cFormats) {}

 
HWND
STDCALL
GetOpenClipboardWindow(
		       VOID) {}

 
/* Despite the A these are ASCII functions! */
LPSTR
STDCALL
CharNextExA(
	    WORD CodePage,
	    LPCSTR lpCurrentChar,
	    DWORD dwFlags) {}

 
LPSTR
STDCALL
CharPrevExA(
	    WORD CodePage,
	    LPCSTR lpStart,
	    LPCSTR lpCurrentChar,
	    DWORD dwFlags) {}

 
HWND
STDCALL
SetFocus(
	 HWND hWnd) {}

 
HWND
STDCALL
GetActiveWindow(
		VOID) {}

 
HWND
STDCALL
GetFocus(
	 VOID) {}

 
UINT
STDCALL
GetKBCodePage(
	      VOID) {}

 
SHORT
STDCALL
GetKeyState(
	    int nVirtKey) {}

 
SHORT
STDCALL
GetAsyncKeyState(
		 int vKey) {}

 
WINBOOL
STDCALL
GetKeyboardState(
		 PBYTE lpKeyState) {}

 
WINBOOL
STDCALL
SetKeyboardState(
		 LPBYTE lpKeyState) {}

 
int
STDCALL
GetKeyboardType(
		int nTypeFlag) {}

 
int
STDCALL
ToAscii(
	UINT uVirtKey,
	UINT uScanCode,
	PBYTE lpKeyState,
	LPWORD lpChar,
	UINT uFlags) {}

 
int
STDCALL
ToAsciiEx(
	  UINT uVirtKey,
	  UINT uScanCode,
	  PBYTE lpKeyState,
	  LPWORD lpChar,
	  UINT uFlags,
	  HKL dwhkl) {}

 
int
STDCALL
ToUnicode(
	  UINT wVirtKey,
	  UINT wScanCode,
	  PBYTE lpKeyState,
	  LPWSTR pwszBuff,
	  int cchBuff,
	  UINT wFlags) {}

 
DWORD
STDCALL
OemKeyScan(
	   WORD wOemChar) {}

 
VOID
STDCALL
keybd_event(
	    BYTE bVk,
	    BYTE bScan,
	    DWORD dwFlags,
	    DWORD dwExtraInfo) {}

 
VOID
STDCALL
mouse_event(
	    DWORD dwFlags,
	    DWORD dx,
	    DWORD dy,
	    DWORD cButtons,
	    DWORD dwExtraInfo) {}

WINBOOL
STDCALL
GetInputState(
	      VOID) {}

 
DWORD
STDCALL
GetQueueStatus(
	       UINT flags) {}

 
HWND
STDCALL
GetCapture(
	   VOID) {}

 
HWND
STDCALL
SetCapture(
	   HWND hWnd) {}

 
WINBOOL
STDCALL
ReleaseCapture(
	       VOID) {}

 
DWORD
STDCALL
MsgWaitForMultipleObjects(
			  DWORD nCount,
			  LPHANDLE pHandles,
			  WINBOOL fWaitAll,
			  DWORD dwMilliseconds,
			  DWORD dwWakeMask) {}

 
UINT
STDCALL
SetTimer(
	 HWND hWnd ,
	 UINT nIDEvent,
	 UINT uElapse,
	 TIMERPROC lpTimerFunc) {}

 
WINBOOL
STDCALL
KillTimer(
	  HWND hWnd,
	  UINT uIDEvent) {}

 
WINBOOL
STDCALL
IsWindowUnicode(
		HWND hWnd) {}

 
WINBOOL
STDCALL
EnableWindow(
	     HWND hWnd,
	     WINBOOL bEnable) {}

 
WINBOOL
STDCALL
IsWindowEnabled(
		HWND hWnd) {}

 
WINBOOL
STDCALL
DestroyAcceleratorTable(
			HACCEL hAccel) {}

int
STDCALL
GetSystemMetrics(
		 int nIndex) {}

HMENU
STDCALL
GetMenu(
	HWND hWnd) {}

 
WINBOOL
STDCALL
SetMenu(
	HWND hWnd,
	HMENU hMenu) {}

 
WINBOOL
STDCALL
HiliteMenuItem(
	       HWND hWnd,
	       HMENU hMenu,
	       UINT uIDHiliteItem,
	       UINT uHilite) {}

 
UINT
STDCALL
GetMenuState(
	     HMENU hMenu,
	     UINT uId,
	     UINT uFlags) {}

 
WINBOOL
STDCALL
DrawMenuBar(
	    HWND hWnd) {}

 
HMENU
STDCALL
GetSystemMenu(
	      HWND hWnd,
	      WINBOOL bRevert) {}

 
HMENU
STDCALL
CreateMenu(
	   VOID) {}

 
HMENU
STDCALL
CreatePopupMenu(
		VOID) {}

 
WINBOOL
STDCALL
DestroyMenu(
	    HMENU hMenu) {}

 
DWORD
STDCALL
CheckMenuItem(
	      HMENU hMenu,
	      UINT uIDCheckItem,
	      UINT uCheck) {}

 
WINBOOL
STDCALL
EnableMenuItem(
	       HMENU hMenu,
	       UINT uIDEnableItem,
	       UINT uEnable) {}

 
HMENU
STDCALL
GetSubMenu(
	   HMENU hMenu,
	   int nPos) {}

 
UINT
STDCALL
GetMenuItemID(
	      HMENU hMenu,
	      int nPos) {}

 
int
STDCALL
GetMenuItemCount(
		 HMENU hMenu) {}

WINBOOL
STDCALL RemoveMenu(
		   HMENU hMenu,
		   UINT uPosition,
		   UINT uFlags) {}

 
WINBOOL
STDCALL
DeleteMenu(
	   HMENU hMenu,
	   UINT uPosition,
	   UINT uFlags) {}

 
WINBOOL
STDCALL
SetMenuItemBitmaps(
		   HMENU hMenu,
		   UINT uPosition,
		   UINT uFlags,
		   HBITMAP hBitmapUnchecked,
		   HBITMAP hBitmapChecked) {}

 
LONG
STDCALL
GetMenuCheckMarkDimensions(
			   VOID) {}

 
WINBOOL
STDCALL
TrackPopupMenu(
	       HMENU hMenu,
	       UINT uFlags,
	       int x,
	       int y,
	       int nReserved,
	       HWND hWnd,
	       CONST RECT *prcRect) {}

UINT
STDCALL
GetMenuDefaultItem(
		   HMENU hMenu, 
		   UINT fByPos, 
		   UINT gmdiFlags) {}

WINBOOL
STDCALL
SetMenuDefaultItem(
		   HMENU hMenu, 
		   UINT uItem, 
		   UINT fByPos) {}

WINBOOL
STDCALL
GetMenuItemRect(HWND hWnd, 
		HMENU hMenu, 
		UINT uItem, 
		LPRECT lprcItem) {}

int
STDCALL
MenuItemFromPoint(HWND hWnd, 
		  HMENU hMenu, 
		  POINT ptScreen) {}

 
DWORD
STDCALL
DragObject(HWND hWnd, HWND hWnd1, UINT v, DWORD d, HCURSOR hCursor) {}

 
WINBOOL
STDCALL
DragDetect(HWND hwnd, 
	   POINT pt) {}

 
WINBOOL
STDCALL
DrawIcon(
	 HDC hDC,
	 int X,
	 int Y,
	 HICON hIcon) {}

WINBOOL
STDCALL
UpdateWindow(
	     HWND hWnd) {}

 
HWND
STDCALL
SetActiveWindow(
		HWND hWnd) {}

 
HWND
STDCALL
GetForegroundWindow(
		    VOID) {}

WINBOOL
STDCALL
PaintDesktop(HDC hdc) {}

 
WINBOOL
STDCALL
SetForegroundWindow(
		    HWND hWnd) {}

 
HWND
STDCALL
WindowFromDC(
	     HDC hDC) {}

 
HDC
STDCALL
GetDC(
      HWND hWnd) {}

 
HDC
STDCALL
GetDCEx(
	HWND hWnd ,
	HRGN hrgnClip,
	DWORD flags) {}

 
HDC
STDCALL
GetWindowDC(
	    HWND hWnd) {}

 
int
STDCALL
ReleaseDC(
	  HWND hWnd,
	  HDC hDC) {}

 
HDC
STDCALL
BeginPaint(
	   HWND hWnd,
	   LPPAINTSTRUCT lpPaint) {}

 
WINBOOL
STDCALL
EndPaint(
	 HWND hWnd,
	 CONST PAINTSTRUCT *lpPaint) {}

 
WINBOOL
STDCALL
GetUpdateRect(
	      HWND hWnd,
	      LPRECT lpRect,
	      WINBOOL bErase) {}

 
int
STDCALL
GetUpdateRgn(
	     HWND hWnd,
	     HRGN hRgn,
	     WINBOOL bErase) {}

 
int
STDCALL
SetWindowRgn(
	     HWND hWnd,
	     HRGN hRgn,
	     WINBOOL bRedraw) {}

 
int
STDCALL
GetWindowRgn(
	     HWND hWnd,
	     HRGN hRgn) {}

 
int
STDCALL
ExcludeUpdateRgn(
		 HDC hDC,
		 HWND hWnd) {}

 
WINBOOL
STDCALL
InvalidateRect(
	       HWND hWnd ,
	       CONST RECT *lpRect,
	       WINBOOL bErase) {}

 
WINBOOL
STDCALL
ValidateRect(
	     HWND hWnd ,
	     CONST RECT *lpRect) {}

 
WINBOOL
STDCALL
InvalidateRgn(
	      HWND hWnd,
	      HRGN hRgn,
	      WINBOOL bErase) {}

 
WINBOOL
STDCALL
ValidateRgn(
	    HWND hWnd,
	    HRGN hRgn) {}

 
WINBOOL
STDCALL
RedrawWindow(
	     HWND hWnd,
	     CONST RECT *lprcUpdate,
	     HRGN hrgnUpdate,
	     UINT flags) {}

 
WINBOOL
STDCALL
LockWindowUpdate(
		 HWND hWndLock) {}

 
WINBOOL
STDCALL
ScrollWindow(
	     HWND hWnd,
	     int XAmount,
	     int YAmount,
	     CONST RECT *lpRect,
	     CONST RECT *lpClipRect) {}

 
WINBOOL
STDCALL
ScrollDC(
	 HDC hDC,
	 int dx,
	 int dy,
	 CONST RECT *lprcScroll,
	 CONST RECT *lprcClip ,
	 HRGN hrgnUpdate,
	 LPRECT lprcUpdate) {}

 
int
STDCALL
ScrollWindowEx(
	       HWND hWnd,
	       int dx,
	       int dy,
	       CONST RECT *prcScroll,
	       CONST RECT *prcClip ,
	       HRGN hrgnUpdate,
	       LPRECT prcUpdate,
	       UINT flags) {}

 
int
STDCALL
SetScrollPos(
	     HWND hWnd,
	     int nBar,
	     int nPos,
	     WINBOOL bRedraw) {}

 
int
STDCALL
GetScrollPos(
	     HWND hWnd,
	     int nBar) {}

 
WINBOOL
STDCALL
SetScrollRange(
	       HWND hWnd,
	       int nBar,
	       int nMinPos,
	       int nMaxPos,
	       WINBOOL bRedraw) {}

 
WINBOOL
STDCALL
GetScrollRange(
	       HWND hWnd,
	       int nBar,
	       LPINT lpMinPos,
	       LPINT lpMaxPos) {}

 
WINBOOL
STDCALL
ShowScrollBar(
	      HWND hWnd,
	      int wBar,
	      WINBOOL bShow) {}

 
WINBOOL
STDCALL
EnableScrollBar(
		HWND hWnd,
		UINT wSBflags,
		UINT wArrows) {}

 
WINBOOL
STDCALL
GetClientRect(
	      HWND hWnd,
	      LPRECT lpRect) {}

 
WINBOOL
STDCALL
GetWindowRect(
	      HWND hWnd,
	      LPRECT lpRect) {}

 
WINBOOL
STDCALL
AdjustWindowRect(
		 LPRECT lpRect,
		 DWORD dwStyle,
		 WINBOOL bMenu) {}

 
WINBOOL
STDCALL
AdjustWindowRectEx(
		   LPRECT lpRect,
		   DWORD dwStyle,
		   WINBOOL bMenu,
		   DWORD dwExStyle) {}

WINBOOL
STDCALL
SetWindowContextHelpId(HWND hWnd, DWORD d) {}

DWORD
STDCALL
GetWindowContextHelpId(HWND hWnd) {}

WINBOOL
STDCALL
SetMenuContextHelpId(HMENU hMenu, DWORD d) {}

DWORD
STDCALL
GetMenuContextHelpId(HMENU hMenu) {}

 
WINBOOL
STDCALL
MessageBeep(
	    UINT uType) {}

 
int
STDCALL
ShowCursor(
	   WINBOOL bShow) {}

 
WINBOOL
STDCALL
SetCursorPos(
	     int X,
	     int Y) {}

 
HCURSOR
STDCALL
SetCursor(
	  HCURSOR hCursor) {}

 
WINBOOL
STDCALL
GetCursorPos(
	     LPPOINT lpPoint) {}

 
WINBOOL
STDCALL
ClipCursor(
	   CONST RECT *lpRect) {}

 
WINBOOL
STDCALL
GetClipCursor(
	      LPRECT lpRect) {}

 
HCURSOR
STDCALL
GetCursor(
	  VOID) {}

 
WINBOOL
STDCALL
CreateCaret(
	    HWND hWnd,
	    HBITMAP hBitmap ,
	    int nWidth,
	    int nHeight) {}

 
UINT
STDCALL
GetCaretBlinkTime(
		  VOID) {}

 
WINBOOL
STDCALL
SetCaretBlinkTime(
		  UINT uMSeconds) {}

 
WINBOOL
STDCALL
DestroyCaret(
	     VOID) {}

 
WINBOOL
STDCALL
HideCaret(
	  HWND hWnd) {}

 
WINBOOL
STDCALL
ShowCaret(
	  HWND hWnd) {}

 
WINBOOL
STDCALL
SetCaretPos(
	    int X,
	    int Y) {}

 
WINBOOL
STDCALL
GetCaretPos(
	    LPPOINT lpPoint) {}

 
WINBOOL
STDCALL
ClientToScreen(
	       HWND hWnd,
	       LPPOINT lpPoint) {}

 
WINBOOL
STDCALL
ScreenToClient(
	       HWND hWnd,
	       LPPOINT lpPoint) {}

 
int
STDCALL
MapWindowPoints(
		HWND hWndFrom,
		HWND hWndTo,
		LPPOINT lpPoints,
		UINT cPoints) {}

 
HWND
STDCALL
WindowFromPoint(
		POINT Point) {}

 
HWND
STDCALL
ChildWindowFromPoint(
		     HWND hWndParent,
		     POINT Point) {}

 
DWORD
STDCALL
GetSysColor(
	    int nIndex) {}

 
HBRUSH
STDCALL
GetSysColorBrush(
		 int nIndex) {}

 
WINBOOL
STDCALL
SetSysColors(
	     int cElements,
	     CONST INT * lpaElements,
	     CONST COLORREF * lpaRgbValues) {}

 
WINBOOL
STDCALL
DrawFocusRect(
	      HDC hDC,
	      CONST RECT * lprc) {}

 
int
STDCALL
FillRect(
	 HDC hDC,
	 CONST RECT *lprc,
	 HBRUSH hbr) {}

 
int
STDCALL
FrameRect(
	  HDC hDC,
	  CONST RECT *lprc,
	  HBRUSH hbr) {}

 
WINBOOL
STDCALL
InvertRect(
	   HDC hDC,
	   CONST RECT *lprc) {}

 
WINBOOL
STDCALL
SetRect(
	LPRECT lprc,
	int xLeft,
	int yTop,
	int xRight,
	int yBottom) {}

 
WINBOOL
STDCALL
SetRectEmpty(
	     LPRECT lprc) {}

 
WINBOOL
STDCALL
CopyRect(
	 LPRECT lprcDst,
	 CONST RECT *lprcSrc) {}

 
WINBOOL
STDCALL
InflateRect(
	    LPRECT lprc,
	    int dx,
	    int dy) {}

 
WINBOOL
STDCALL
IntersectRect(
	      LPRECT lprcDst,
	      CONST RECT *lprcSrc1,
	      CONST RECT *lprcSrc2) {}

 
WINBOOL
STDCALL
UnionRect(
	  LPRECT lprcDst,
	  CONST RECT *lprcSrc1,
	  CONST RECT *lprcSrc2) {}

 
WINBOOL
STDCALL
SubtractRect(
	     LPRECT lprcDst,
	     CONST RECT *lprcSrc1,
	     CONST RECT *lprcSrc2) {}

 
WINBOOL
STDCALL
OffsetRect(
	   LPRECT lprc,
	   int dx,
	   int dy) {}

 
WINBOOL
STDCALL
IsRectEmpty(
	    CONST RECT *lprc) {}

 
WINBOOL
STDCALL
EqualRect(
	  CONST RECT *lprc1,
	  CONST RECT *lprc2) {}

 
WINBOOL
STDCALL
PtInRect(
	 CONST RECT *lprc,
	 POINT pt) {}

 
WORD
STDCALL
GetWindowWord(
	      HWND hWnd,
	      int nIndex) {}

 
WORD
STDCALL
SetWindowWord(
	      HWND hWnd,
	      int nIndex,
	      WORD wNewWord) {}

 
WORD
STDCALL
GetClassWord(
	     HWND hWnd,
	     int nIndex) {}

 
WORD
STDCALL
SetClassWord(
	     HWND hWnd,
	     int nIndex,
	     WORD wNewWord) {}

HWND
STDCALL
GetDesktopWindow(
		 VOID) {}

 
HWND
STDCALL
GetParent(
	  HWND hWnd) {}

 
HWND
STDCALL
SetParent(
	  HWND hWndChild,
	  HWND hWndNewParent) {}

 
WINBOOL
STDCALL
EnumChildWindows(
		 HWND hWndParent,
		 ENUMWINDOWSPROC lpEnumFunc,
		 LPARAM lParam) {}

 
WINBOOL
STDCALL
EnumWindows(
	    ENUMWINDOWSPROC lpEnumFunc,
	    LPARAM lParam) {}

 
WINBOOL
STDCALL
EnumThreadWindows(
		  DWORD dwThreadId,
		  ENUMWINDOWSPROC lpfn,
		  LPARAM lParam) {}

HWND
STDCALL
GetTopWindow(
	     HWND hWnd) {}

 
DWORD
STDCALL
GetWindowThreadProcessId(
			 HWND hWnd,
			 LPDWORD lpdwProcessId) {}

#define GetWindowTask(hWnd) \
	((HANDLE)GetWindowThreadProcessId(hWnd, NULL))
 
HWND
STDCALL
GetLastActivePopup(
		   HWND hWnd) {}

 
HWND
STDCALL
GetWindow(
	  HWND hWnd,
	  UINT uCmd) {}

WINBOOL
STDCALL
UnhookWindowsHook(
		  int nCode,
		  HOOKPROC pfnFilterProc) {}

WINBOOL
STDCALL
UnhookWindowsHookEx(
		    HHOOK hhk) {}

 
LRESULT
STDCALL
CallNextHookEx(
	       HHOOK hhk,
	       int nCode,
	       WPARAM wParam,
	       LPARAM lParam) {}

 
WINBOOL
STDCALL
CheckMenuRadioItem(HMENU hMenu, UINT v1, UINT v2, UINT v3, UINT v4) {}

HCURSOR
STDCALL
CreateCursor(
	     HINSTANCE hInst,
	     int xHotSpot,
	     int yHotSpot,
	     int nWidth,
	     int nHeight,
	     CONST VOID *pvANDPlane,
	     CONST VOID *pvXORPlane) {}

 
WINBOOL
STDCALL
DestroyCursor(
	      HCURSOR hCursor) {}

 
WINBOOL
STDCALL
SetSystemCursor(
		HCURSOR hcur,
		DWORD   anID) {}

 
HICON
STDCALL
CreateIcon(
	   HINSTANCE hInstance,
	   int nWidth,
	   int nHeight,
	   BYTE cPlanes,
	   BYTE cBitsPixel,
	   CONST BYTE *lpbANDbits,
	   CONST BYTE *lpbXORbits) {}

 
WINBOOL
STDCALL
DestroyIcon(
	    HICON hIcon) {}

 
int
STDCALL
LookupIconIdFromDirectory(
			  PBYTE presbits,
			  WINBOOL fIcon) {}

 
int
STDCALL
LookupIconIdFromDirectoryEx(
			    PBYTE presbits,
			    WINBOOL  fIcon,
			    int   cxDesired,
			    int   cyDesired,
			    UINT  Flags) {}

 
HICON
STDCALL
CreateIconFromResource(
		       PBYTE presbits,
		       DWORD dwResSize,
		       WINBOOL fIcon,
		       DWORD dwVer) {}

 
HICON
STDCALL
CreateIconFromResourceEx(
			 PBYTE presbits,
			 DWORD dwResSize,
			 WINBOOL  fIcon,
			 DWORD dwVer,
			 int   cxDesired,
			 int   cyDesired,
			 UINT  Flags) {}

 
HICON
STDCALL
CopyImage(
	  HANDLE h,
	  UINT v1,
	  int v2,
	  int v3,
	  UINT v4) {}

 
HICON
STDCALL
CreateIconIndirect(
		   PICONINFO piconinfo) {}

 
HICON
STDCALL
CopyIcon(
	 HICON hIcon) {}

 
WINBOOL
STDCALL
GetIconInfo(
	    HICON hIcon,
	    PICONINFO piconinfo) {}

 
WINBOOL
STDCALL
MapDialogRect(
	      HWND hDlg,
	      LPRECT lpRect) {}

int
STDCALL
SetScrollInfo(HWND hWnd, int v, LPCSCROLLINFO scrollInfo, WINBOOL b) {}

WINBOOL
STDCALL
GetScrollInfo(HWND hWnd, int v, LPSCROLLINFO scrollInfo) {}

WINBOOL
STDCALL
TranslateMDISysAccel(
		     HWND hWndClient,
		     LPMSG lpMsg) {}

 
UINT
STDCALL
ArrangeIconicWindows(
		     HWND hWnd) {}

WORD
STDCALL
TileWindows(HWND hwndParent, UINT wHow, CONST RECT * lpRect, UINT cKids, const HWND *lpKids) {}

WORD
STDCALL
CascadeWindows(HWND hwndParent, UINT wHow, CONST RECT * lpRect, UINT cKids,  const HWND *lpKids) {}

 
VOID
STDCALL
SetLastErrorEx(
	       DWORD dwErrCode,
	       DWORD dwType
	       ) {}

 
VOID
STDCALL
SetDebugErrorLevel(
		   DWORD dwLevel
		   ) {}

WINBOOL
STDCALL
DrawEdge(HDC hdc, LPRECT qrc, UINT edge, UINT grfFlags) {}

WINBOOL
STDCALL
DrawFrameControl(HDC hDC, LPRECT rect, UINT v1, UINT v2) {}

WINBOOL
STDCALL
DrawCaption(HWND hWnd, HDC hDC, CONST RECT *rect, UINT v1) {}

WINBOOL
STDCALL
DrawAnimatedRects(HWND hwnd, int idAni, CONST RECT * lprcFrom, CONST RECT * lprcTo) {}

WINBOOL
STDCALL
TrackPopupMenuEx(HMENU hMenu, UINT v1, int v2, int v3, HWND hWnd,
		LPTPMPARAMS params) {}

HWND
STDCALL
ChildWindowFromPointEx(HWND hWnd, POINT pt, UINT v) {}

WINBOOL
STDCALL
DrawIconEx(HDC hdc, int xLeft, int yTop,
	   HICON hIcon, int cxWidth, int cyWidth,
	   UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags) {}

WINBOOL
STDCALL
AnimatePalette(HPALETTE hPalette, UINT v1, UINT v2,
	CONST PALETTEENTRY *palEntry) {}

WINBOOL
STDCALL
Arc(HDC hDC, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8) {}

WINBOOL
STDCALL
BitBlt(HDC hDst, int v1, int v2, int v3, int v4,
	HDC hdc1, int v5, int v6, DWORD dWord) {}

WINBOOL
STDCALL
CancelDC(HDC hDC) {}

WINBOOL
STDCALL
Chord(HDC hDC, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8) {}

HMETAFILE
STDCALL
CloseMetaFile(HDC hDC) {}

int
STDCALL
CombineRgn(HRGN hRgn1, HRGN hRgn2, HRGN hRgn3, int v) {}

HBITMAP
STDCALL
CreateBitmap(int v1, int v2, UINT v3, UINT v4, CONST VOID *ptr) {}

HBITMAP
STDCALL
CreateBitmapIndirect(CONST BITMAP *pbm) {}

HBRUSH
STDCALL
CreateBrushIndirect(CONST LOGBRUSH *logBrush) {}

HBITMAP
STDCALL
CreateCompatibleBitmap(HDC hDC, int v1, int v2) {}

HBITMAP
STDCALL
CreateDiscardableBitmap(HDC hDC, int v1, int v2) {}

HDC
STDCALL
CreateCompatibleDC(HDC hDC) {}

HBITMAP
STDCALL
CreateDIBitmap(HDC hDC, CONST BITMAPINFOHEADER *bmInfoHdr,
	DWORD dWord, CONST VOID *ptr, CONST BITMAPINFO *bmInfo, UINT v) {}

HBRUSH
STDCALL
CreateDIBPatternBrush(HGLOBAL hGlobal, UINT v) {}

HBRUSH
STDCALL
CreateDIBPatternBrushPt(CONST VOID *ptr, UINT v) {}

HRGN
STDCALL
CreateEllipticRgn(int v1, int v2, int v3, int v4) {}

HRGN
STDCALL
CreateEllipticRgnIndirect(CONST RECT *r) {}

HBRUSH
STDCALL
CreateHatchBrush(int v, COLORREF color) {}

HPALETTE
STDCALL
CreatePalette(CONST LOGPALETTE *palette) {}

HPEN
STDCALL
CreatePen(int v1, int v2, COLORREF color) {}

HPEN
STDCALL
CreatePenIndirect(CONST LOGPEN *logPen) {}

HRGN
STDCALL
CreatePolyPolygonRgn(CONST POINT *pt, CONST INT *pint, int v1, int v2) {}

HBRUSH
STDCALL
CreatePatternBrush(HBITMAP hBitmap) {}

HRGN
STDCALL
CreateRectRgn(int v1, int v2, int v3, int v4) {}

HRGN
STDCALL
CreateRectRgnIndirect(CONST RECT *rect) {}

HRGN
STDCALL
CreateRoundRectRgn(int v1, int v2, int v3, int v4, int v5, int v6) {}

HBRUSH
STDCALL
CreateSolidBrush(COLORREF color) {}

WINBOOL
STDCALL
DeleteDC(HDC hDC) {}

WINBOOL
STDCALL
DeleteMetaFile(HMETAFILE hMetaFile) {}

WINBOOL
STDCALL
DeleteObject(HGDIOBJ hGdiObj) {}

int
STDCALL
DrawEscape(HDC hDC, int v1, int v2, LPCSTR str) {}

WINBOOL
STDCALL
Ellipse(HDC hDC, int v1, int v2, int v3, int v4) {}

int
STDCALL
EnumObjects(HDC hDC, int v1, ENUMOBJECTSPROC enumObjProc, LPARAM lParam) {}

WINBOOL
STDCALL
EqualRgn(HRGN hRgn, HRGN hRgn1) {}

int
STDCALL
Escape(HDC hDC, int v1, int v2, LPCSTR str, LPVOID ptr) {}

int
STDCALL
ExtEscape(HDC hDC, int v1, int v2, LPCSTR str1, int v3, LPSTR str2) {}

int
STDCALL
ExcludeClipRect(HDC hDC, int v1, int v2, int v3, int v4) {}

HRGN
STDCALL
ExtCreateRegion(CONST XFORM *xForm, DWORD d1, CONST RGNDATA *rgn) {}

WINBOOL
STDCALL
ExtFloodFill(HDC hDC, int v1, int v2, COLORREF color, UINT v3) {}

WINBOOL
STDCALL
FillRgn(HDC hDC, HRGN hRgn, HBRUSH hBrush) {}

WINBOOL
STDCALL
FloodFill(HDC hDC, int v1, int v2, COLORREF color) {}

WINBOOL
STDCALL
FrameRgn(HDC hDC, HRGN hRgn, HBRUSH hBrush, int v1, int v2) {}

int
STDCALL
GetROP2(HDC hDC) {}

WINBOOL
STDCALL
GetAspectRatioFilterEx(HDC hDC, LPSIZE size) {}

COLORREF
STDCALL
GetBkColor(HDC hDC) {}

int
STDCALL
GetBkMode(HDC hDC) {}

LONG
STDCALL
GetBitmapBits(HBITMAP hBitmap, LONG v, LPVOID ptr) {}

WINBOOL
STDCALL
GetBitmapDimensionEx(HBITMAP hBitmap, LPSIZE size) {}

UINT
STDCALL
GetBoundsRect(HDC hDC, LPRECT rect, UINT v) {}

WINBOOL
STDCALL
GetBrushOrgEx(HDC hDC, LPPOINT pt) {}

int
STDCALL
GetClipBox(HDC hDC, LPRECT rect) {}

int
STDCALL
GetClipRgn(HDC hDC, HRGN hRgn) {}

int
STDCALL
GetMetaRgn(HDC hDC, HRGN hRgn) {}

HGDIOBJ
STDCALL
GetCurrentObject(HDC hDC, UINT v) {}

WINBOOL
STDCALL
GetCurrentPositionEx(HDC hDC, LPPOINT pt) {}

int
STDCALL
GetDeviceCaps(HDC hDC, int v) {}

int
STDCALL
GetDIBits(HDC hDC, HBITMAP hbm, UINT v1, UINT v2, LPVOID ptr,
	LPBITMAPINFO bmMapInfo, UINT v3) {}

DWORD
STDCALL
GetFontData(HDC hDC, DWORD d1, DWORD d2, LPVOID ptr, DWORD d3) {}

int
STDCALL
GetGraphicsMode(HDC hDC) {}

int
STDCALL
GetMapMode(HDC hDC) {}

UINT
STDCALL
GetMetaFileBitsEx(HMETAFILE hMetaFile, UINT v1, LPVOID ptr) {}

COLORREF
STDCALL
GetNearestColor(HDC hDC, COLORREF color) {}

UINT
STDCALL
GetNearestPaletteIndex(HPALETTE hPalette, COLORREF color) {}

DWORD
STDCALL
GetObjectType(HGDIOBJ h) {}

UINT
STDCALL
GetPaletteEntries(HPALETTE hPalette, UINT v1, UINT v2, LPPALETTEENTRY palEntry) {}

COLORREF
STDCALL
GetPixel(HDC hDC, int v1, int v2) {}

/*int
STDCALL
GetPixelFormat(HDC hDC) {} */

int
STDCALL
GetPolyFillMode(HDC hDC) {}

WINBOOL
STDCALL
GetRasterizerCaps(LPRASTERIZER_STATUS rasterizerStatus, UINT v) {}

DWORD
STDCALL
GetRegionData(HRGN hRgn, DWORD d1, LPRGNDATA rgndata) {}

int
STDCALL
GetRgnBox(HRGN hRgn, LPRECT rect) {}

HGDIOBJ
STDCALL
GetStockObject(int v) {}

int
STDCALL
GetStretchBltMode(HDC hDC) {}

UINT
STDCALL
GetSystemPaletteEntries(HDC hDC, UINT v1, UINT v2, LPPALETTEENTRY palEntry) {}

UINT
STDCALL
GetSystemPaletteUse(HDC hDC) {}

int
STDCALL
GetTextCharacterExtra(HDC hDC) {}

UINT
STDCALL
GetTextAlign(HDC hDC) {}

COLORREF
STDCALL
GetTextColor(HDC hDC) {}

int
STDCALL
GetTextCharset(HDC hdc) {}

int
STDCALL
GetTextCharsetInfo(HDC hdc, LPFONTSIGNATURE lpSig, DWORD dwFlags) {}

WINBOOL
STDCALL
TranslateCharsetInfo( DWORD *lpSrc, LPCHARSETINFO lpCs, DWORD dwFlags) {}

DWORD
STDCALL
GetFontLanguageInfo( HDC  hDC) {}

WINBOOL
STDCALL
GetViewportExtEx(HDC hDC, LPSIZE size) {}

WINBOOL
STDCALL
GetViewportOrgEx(HDC hDC, LPPOINT pt) {}

WINBOOL
STDCALL
GetWindowExtEx(HDC hDC, LPSIZE size) {}

WINBOOL
STDCALL
GetWindowOrgEx(HDC hDC, LPPOINT pt) {}

int
STDCALL
IntersectClipRect(HDC hDC, int v1, int v2, int v3, int v4) {}

WINBOOL
STDCALL
InvertRgn(HDC hDC, HRGN hRgn) {}

WINBOOL
STDCALL
LineDDA(int v1, int v2, int v3, int v4, LINEDDAPROC ddaproc, LPARAM lParam) {}

WINBOOL
STDCALL
LineTo(HDC hDC, int v1, int v2) {}

WINBOOL
STDCALL
MaskBlt(HDC hDC, int v1, int v2, int v3, int v4,
	HDC hdc1, int v5, int v6, HBITMAP hbm, int v7, int v8, DWORD v9) {}

WINBOOL
STDCALL
PlgBlt(HDC hDC, CONST POINT *pt, HDC hdc1, int v1, int v2, int v3,
       int v4, HBITMAP hbm, int v5, int v6) {}

int
STDCALL
OffsetClipRgn(HDC hDC, int v1, int v2) {}

int
STDCALL
OffsetRgn(HRGN hRgn, int v1, int v2) {}

WINBOOL
STDCALL 
PatBlt(HDC hDC, int v1, int v2, int v3, int v4, DWORD d1) {}

WINBOOL
STDCALL
Pie(HDC hDC, int v1, int v2, int v3, int v4, int v5, int v6, int v7, int v8) {}

WINBOOL
STDCALL
PlayMetaFile(HDC hDC, HMETAFILE hmetaFile) {}

WINBOOL
STDCALL
PaintRgn(HDC hDC, HRGN hRgn) {}

WINBOOL
STDCALL
PolyPolygon(HDC hDC, CONST POINT *pt, CONST INT *v1, int v2) {}

WINBOOL
STDCALL
PtInRegion(HRGN hRgn, int v1, int v2) {}

WINBOOL
STDCALL
PtVisible(HDC hDC, int v1, int v2) {}

WINBOOL
STDCALL
RectInRegion(HRGN hRgn, CONST RECT *rect) {}

WINBOOL
STDCALL
RectVisible(HDC hDC, CONST RECT *rect) {}

WINBOOL
STDCALL
Rectangle(HDC hDC, int v1, int v2, int v3, int v4) {}

WINBOOL
STDCALL
RestoreDC(HDC hDC, int v1) {}

UINT
STDCALL
RealizePalette(HDC hDC) {}

WINBOOL
STDCALL
RoundRect(HDC hDC, int v1, int v2, int v3, int v4, int v5, int v6) {}

WINBOOL
STDCALL
ResizePalette(HPALETTE hPalette, UINT v1) {}

int
STDCALL
SaveDC(HDC hDC) {}

int
STDCALL
SelectClipRgn(HDC hDC, HRGN hRgn) {}

int
STDCALL
ExtSelectClipRgn(HDC hDC, HRGN hRgn, int v1) {}

int
STDCALL
SetMetaRgn(HDC hDC) {}

HGDIOBJ
STDCALL
SelectObject(HDC hDC, HGDIOBJ hGdiObj) {}

HPALETTE
STDCALL
SelectPalette(HDC hDC, HPALETTE hpalette, WINBOOL b1) {}

COLORREF
STDCALL
SetBkColor(HDC hDC, COLORREF color) {}

int
STDCALL
SetBkMode(HDC hDC, int mode) {}

LONG
STDCALL
SetBitmapBits(HBITMAP hbm, DWORD d1, CONST VOID *ptr) {}

UINT
STDCALL
SetBoundsRect(HDC hDC, CONST RECT *rect, UINT v) {}

int
STDCALL
SetDIBits(HDC hDC, HBITMAP hbm, UINT v1, UINT v2, CONST VOID *ptr,
	CONST BITMAPINFO *bmInfo, UINT v3) {}

int
STDCALL
SetDIBitsToDevice(HDC hDC, int v1, int v2, DWORD d1, DWORD d2, int v3,
		  int v4, UINT v5, UINT v6, CONST VOID *ptr,
		CONST BITMAPINFO *bmInfo, UINT v7) {}

DWORD
STDCALL
SetMapperFlags(HDC hDC, DWORD v) {}

int
STDCALL
SetGraphicsMode(HDC hdc, int iMode) {}

int
STDCALL
SetMapMode(HDC hDC, int v) {}

HMETAFILE
STDCALL
SetMetaFileBitsEx(UINT v, CONST BYTE *ptr) {}

UINT
STDCALL
SetPaletteEntries(HPALETTE hPalette, UINT v1, UINT v2,
	CONST PALETTEENTRY *palEntry) {}

COLORREF
STDCALL
SetPixel(HDC hDC, int v1, int v2, COLORREF color) {}

WINBOOL
STDCALL
SetPixelV(HDC hDC, int v1, int v2, COLORREF color) {}

int
STDCALL
SetPolyFillMode(HDC hDC, int v) {}

WINBOOL
STDCALL
StretchBlt(HDC hDC, int v1, int v2, int v3, int v4,
	HDC hdc1, int v5, int v6, int v7, int v8, DWORD v9) {}

WINBOOL
STDCALL
SetRectRgn(HRGN hRgn, int v1, int v2, int v3, int v4) {}
int
STDCALL
StretchDIBits(HDC hDC, int v1, int v2, int v3, int v4, int v5, int v6,
	int v7, int v8, CONST VOID *ptr, CONST BITMAPINFO *bmInfo,
	UINT v9, DWORD v10) {}

int
STDCALL
SetROP2(HDC hDC, int v) {}

int
STDCALL
SetStretchBltMode(HDC hDC, int v) {}

UINT
STDCALL
SetSystemPaletteUse(HDC hDC, UINT v) {}

int
STDCALL
SetTextCharacterExtra(HDC hDC, int v) {}

COLORREF
STDCALL
SetTextColor(HDC hDC, COLORREF v) {}

UINT
STDCALL
SetTextAlign(HDC hDC, UINT v) {}

WINBOOL
STDCALL
SetTextJustification(HDC hDC, int v1, int v2) {}

WINBOOL
STDCALL
UpdateColors(HDC hDC) {}

WINBOOL
STDCALL
PlayMetaFileRecord(HDC hDC, LPHANDLETABLE hTable, LPMETARECORD metaRecord, UINT v) {}

WINBOOL
STDCALL
EnumMetaFile(HDC hDC, HMETAFILE metaFile,
	ENUMMETAFILEPROC enumMetaFileProc, LPARAM lParam) {}

HENHMETAFILE
STDCALL
CloseEnhMetaFile(HDC hDC) {}

WINBOOL
STDCALL
DeleteEnhMetaFile(HENHMETAFILE hEnMetaFile) {}

WINBOOL
STDCALL
EnumEnhMetaFile(HDC hDC, HENHMETAFILE hEnMetaFile,
		ENHMETAFILEPROC enMetaFileProc, LPVOID ptr, CONST RECT *rect) {}

UINT
STDCALL
GetEnhMetaFileHeader(HENHMETAFILE hEnMetaFile, UINT v, LPENHMETAHEADER mfHdr) {}

UINT
STDCALL
GetEnhMetaFilePaletteEntries(HENHMETAFILE hEnMetaFile, UINT v,
		LPPALETTEENTRY paletteEntry) {}

UINT
STDCALL
GetWinMetaFileBits(HENHMETAFILE hEnMetaFile, UINT v, LPBYTE pb, INT v2, HDC hDC) {}

WINBOOL
STDCALL
PlayEnhMetaFile(HDC hDC, HENHMETAFILE hEnMetFile, CONST RECT *r) {}

WINBOOL
STDCALL
PlayEnhMetaFileRecord(HDC hDC, LPHANDLETABLE hTable,
		CONST ENHMETARECORD *hEnMetaRecord, UINT v) {}

HENHMETAFILE
STDCALL
SetEnhMetaFileBits(UINT v, CONST BYTE *pb) {}

HENHMETAFILE
STDCALL
SetWinMetaFileBits(UINT v, CONST BYTE *pb, HDC hDC,
		CONST METAFILEPICT *metaFilePict) {}

WINBOOL
STDCALL
GdiComment(HDC hDC, UINT v, CONST BYTE *pb) {}

WINBOOL
STDCALL
AngleArc(HDC hDC, int v1, int v2, DWORD d1, FLOAT f1, FLOAT f2) {}

WINBOOL
STDCALL
PolyPolyline(HDC hDC, CONST POINT *pt, CONST DWORD *d1, DWORD d2) {}

WINBOOL
STDCALL
GetWorldTransform(HDC hDC, LPXFORM xForm) {}

WINBOOL
STDCALL
SetWorldTransform(HDC hDC, CONST XFORM *xForm) {}

WINBOOL
STDCALL
ModifyWorldTransform(HDC hDC, CONST XFORM *xForm, DWORD d) {}

WINBOOL
STDCALL
CombineTransform(LPXFORM xForm, CONST XFORM * xForm1, CONST XFORM * xForm2) {}

HBITMAP
STDCALL
CreateDIBSection(HDC hDC, CONST BITMAPINFO *bmInfo,
		UINT v, VOID **ptr, HANDLE h, DWORD d) {}

UINT
STDCALL
GetDIBColorTable(HDC hDC, UINT v1, UINT v2, RGBQUAD rgb) {}

UINT
STDCALL
SetDIBColorTable(HDC hDC, UINT v1, UINT v2, CONST RGBQUAD *rgb) {}

WINBOOL
STDCALL
SetColorAdjustment(HDC hDC, CONST COLORADJUSTMENT *colorAdj) {}

WINBOOL
STDCALL
GetColorAdjustment(HDC hDC, LPCOLORADJUSTMENT colorAdj) {}

HPALETTE
STDCALL 
CreateHalftonePalette(HDC hDC) {}

int
STDCALL
EndDoc(HDC hDC) {}

int
STDCALL
StartPage(HDC hDC) {}

int
STDCALL
EndPage(HDC hDC) {}

int
STDCALL
AbortDoc(HDC hDC) {}

int
STDCALL
SetAbortProc(HDC hDC, ABORTPROC abortProc) {}

WINBOOL
STDCALL
AbortPath(HDC hDC) {}

WINBOOL
STDCALL
ArcTo(HDC hDC, int v1, int v2, int v3, int v4, int v5, int v6,int v7, int v8) {}

WINBOOL
STDCALL
BeginPath(HDC hDC) {}

WINBOOL
STDCALL
CloseFigure(HDC hDC) {}

WINBOOL
STDCALL
EndPath(HDC hDC) {}

WINBOOL
STDCALL
FillPath(HDC hDC) {}

WINBOOL
STDCALL
FlattenPath(HDC hDC) {}

int
STDCALL
GetPath(HDC hDC, LPPOINT pt, LPBYTE pb, int v) {}

HRGN
STDCALL
PathToRegion(HDC hDC) {}

WINBOOL
STDCALL
PolyDraw(HDC hDC, CONST POINT *pt, CONST BYTE *pb, int v) {}

WINBOOL
STDCALL
SelectClipPath(HDC hDC, int v) {}

int
STDCALL
SetArcDirection(HDC hDC, int v) {}

WINBOOL
STDCALL
SetMiterLimit(HDC hDC, FLOAT f, PFLOAT pf) {}

WINBOOL
STDCALL
StrokeAndFillPath(HDC hDC) {}

WINBOOL
STDCALL
StrokePath(HDC hDC) {}

WINBOOL
STDCALL
WidenPath(HDC hDC) {}

HPEN
STDCALL
ExtCreatePen(DWORD d1, DWORD d2, CONST LOGBRUSH *logBrush,
		DWORD d3, CONST DWORD *d4) {}

WINBOOL
STDCALL
GetMiterLimit(HDC hDC, PFLOAT f) {}

int
STDCALL
GetArcDirection(HDC hDC) {}

WINBOOL
STDCALL
MoveToEx(HDC hDC, int v1, int v2, LPPOINT pt) {}

HRGN
STDCALL
CreatePolygonRgn(CONST POINT *pt, int v1, int v2) {}

WINBOOL
STDCALL
DPtoLP(HDC hDC, LPPOINT pt, int v) {}

WINBOOL
STDCALL
LPtoDP(HDC hDC, LPPOINT pt, int v) {}
 
WINBOOL
STDCALL
Polygon(HDC hDC, CONST POINT *pt, int v) {}

WINBOOL
STDCALL
Polyline(HDC hDC, CONST POINT *pt, int v) {}

WINBOOL
STDCALL
PolyBezier(HDC hDC, CONST POINT *pt, DWORD d) {}

WINBOOL
STDCALL
PolyBezierTo(HDC hDC, CONST POINT *pt, DWORD d) {}

WINBOOL
STDCALL
PolylineTo(HDC hDC, CONST POINT *pt, DWORD d) {}

WINBOOL
STDCALL
SetViewportExtEx(HDC hDC, int v1, int v2, LPSIZE size) {}

WINBOOL
STDCALL
SetViewportOrgEx(HDC hDC, int v1, int v2, LPPOINT pt) {}

WINBOOL
STDCALL
SetWindowExtEx(HDC hDC, int v1, int v2, LPSIZE size) {}

WINBOOL
STDCALL
SetWindowOrgEx(HDC hDC, int v1, int v2, LPPOINT pt) {}

WINBOOL
STDCALL
OffsetViewportOrgEx(HDC hDC, int v1, int v2, LPPOINT pt) {}

WINBOOL
STDCALL
OffsetWindowOrgEx(HDC hDC, int v1, int v2, LPPOINT pt) {}

WINBOOL
STDCALL
ScaleViewportExtEx(HDC hDC, int v1, int v2, int v3, int v4, LPSIZE size) {}

WINBOOL
STDCALL
ScaleWindowExtEx(HDC hDC, int v1, int v2, int v3, int v4, LPSIZE size) {}

WINBOOL
STDCALL
SetBitmapDimensionEx(HBITMAP hbm, int v1, int v2, LPSIZE size) {}

WINBOOL
STDCALL
SetBrushOrgEx(HDC hDC, int v1, int v2, LPPOINT pt) {}

WINBOOL
STDCALL
GetDCOrgEx(HDC hDC,LPPOINT pt) {}

WINBOOL
STDCALL
FixBrushOrgEx(HDC hDC,int v1,int v2,LPPOINT pt) {}

WINBOOL
STDCALL
UnrealizeObject(HGDIOBJ hGdiObj) {}

WINBOOL
STDCALL
GdiFlush(void) {}

DWORD
STDCALL
GdiSetBatchLimit(DWORD d) {}

DWORD
STDCALL
GdiGetBatchLimit(void) {}

int
STDCALL
SetICMMode(HDC hDC, int v1) {}

WINBOOL
STDCALL
CheckColorsInGamut(HDC hDC,LPVOID p1,LPVOID p2,DWORD p3) {}

HANDLE
STDCALL
GetColorSpace(HDC hDC) {}

WINBOOL
STDCALL
SetColorSpace(HDC hDC,HCOLORSPACE hColorSpace) {}

WINBOOL
STDCALL
DeleteColorSpace(HCOLORSPACE hColorSpace) {}

WINBOOL
STDCALL
GetDeviceGammaRamp(HDC hDC,LPVOID ptr) {}

WINBOOL
STDCALL
SetDeviceGammaRamp(HDC hDC,LPVOID ptr) {}

WINBOOL
STDCALL
ColorMatchToTarget(HDC hDC,HDC hdc1,DWORD d) {}

HPROPSHEETPAGE
STDCALL
CreatePropertySheetPageA(LPCPROPSHEETPAGE lppsp) {}

WINBOOL
STDCALL
DestroyPropertySheetPage(HPROPSHEETPAGE hPSPage) {}

void
STDCALL
InitCommonControls(void) {}

#define  ImageList_AddIcon(himl, hicon) ImageList_ReplaceIcon(himl, -1, hicon)

HIMAGELIST
STDCALL
ImageList_Create(int cx, int cy, UINT flags, 
		 int cInitial, int cGrow) {}

WINBOOL
STDCALL
ImageList_Destroy(HIMAGELIST himl) {}

int
STDCALL
ImageList_GetImageCount(HIMAGELIST himl) {}

int
STDCALL
ImageList_Add(HIMAGELIST himl, HBITMAP hbmImage, 
	      HBITMAP hbmMask) {}

int
STDCALL
ImageList_ReplaceIcon(HIMAGELIST himl, int i, HICON hicon) {}

COLORREF
STDCALL
ImageList_SetBkColor(HIMAGELIST himl, COLORREF clrBk) {}

COLORREF
STDCALL
ImageList_GetBkColor(HIMAGELIST himl) {}

WINBOOL
STDCALL
ImageList_SetOverlayImage(HIMAGELIST himl, int iImage, 
			  int iOverlay) {}

WINBOOL
STDCALL
ImageList_Draw(HIMAGELIST himl, int i, HDC hdcDst, int x, int y, UINT fStyle) {}

WINBOOL
STDCALL
ImageList_Replace(HIMAGELIST himl, int i, HBITMAP hbmImage, HBITMAP hbmMask) {}

int
STDCALL
ImageList_AddMasked(HIMAGELIST himl, HBITMAP hbmImage, COLORREF crMask) {}

WINBOOL
STDCALL
ImageList_DrawEx(HIMAGELIST himl, int i, HDC hdcDst, int x, int y, int dx, int dy, COLORREF rgbBk, COLORREF rgbFg, UINT fStyle) {}

WINBOOL
STDCALL
ImageList_Remove(HIMAGELIST himl, int i) {}

HICON
STDCALL
ImageList_GetIcon(HIMAGELIST himl, int i, UINT flags) {}

WINBOOL
STDCALL
ImageList_BeginDrag(HIMAGELIST himlTrack, int iTrack, int dxHotspot, int dyHotspot) {}

void
STDCALL
ImageList_EndDrag(void) {}

WINBOOL
STDCALL
ImageList_DragEnter(HWND hwndLock, int x, int y) {}

WINBOOL
STDCALL
ImageList_DragLeave(HWND hwndLock) {}

WINBOOL
STDCALL
ImageList_DragMove(int x, int y) {}

WINBOOL
STDCALL
ImageList_SetDragCursorImage(HIMAGELIST himlDrag, int iDrag, int dxHotspot, int dyHotspot) {}

WINBOOL
STDCALL
ImageList_DragShowNolock(WINBOOL fShow) {}

HIMAGELIST
STDCALL
ImageList_GetDragImage(POINT * ppt,POINT * pptHotspot) {}

WINBOOL
STDCALL
ImageList_GetIconSize(HIMAGELIST himl, int *cx, int *cy) {}

WINBOOL
STDCALL
ImageList_SetIconSize(HIMAGELIST himl, int cx, int cy) {}

WINBOOL
STDCALL
ImageList_GetImageInfo(HIMAGELIST himl, int i, IMAGEINFO * pImageInfo) {}

HIMAGELIST
STDCALL
ImageList_Merge(HIMAGELIST himl1, int i1, HIMAGELIST himl2, int i2, int dx, int dy) {}

HWND
STDCALL
CreateToolbarEx(HWND hwnd, DWORD ws, UINT wID, int nBitmaps,
		HINSTANCE hBMInst, UINT wBMID, LPCTBBUTTON lpButtons,
		int iNumButtons, int dxButton, int dyButton,
		int dxBitmap, int dyBitmap, UINT uStructSize) {}

HBITMAP
STDCALL
CreateMappedBitmap(HINSTANCE hInstance, int idBitmap,
		   UINT wFlags, LPCOLORMAP lpColorMap,
		   int iNumMaps) {}


void
STDCALL
MenuHelp(UINT uMsg, WPARAM wParam, LPARAM lParam, HMENU hMainMenu, HINSTANCE hInst, HWND hwndStatus, UINT *lpwIDs) {}

WINBOOL
STDCALL
ShowHideMenuCtl(HWND hWnd, UINT uFlags, LPINT lpInfo) {}

void
STDCALL
GetEffectiveClientRect(HWND hWnd, LPRECT lprc, LPINT lpInfo) {}

WINBOOL
STDCALL
MakeDragList(HWND hLB) {}

void
STDCALL
DrawInsert(HWND handParent, HWND hLB, int nItem) {}

int
STDCALL
LBItemFromPt(HWND hLB, POINT pt, WINBOOL bAutoScroll) {}

HWND
STDCALL
CreateUpDownControl(DWORD dwStyle, int x, int y, int cx, int cy,
		    HWND hParent, int nID, HINSTANCE hInst,
		    HWND hBuddy,
		    int nUpper, int nLower, int nPos) {}

DWORD
STDCALL
CommDlgExtendedError(VOID) {}

/* Animation controls */

#define Animate_Create(hwndP, id, dwStyle, hInstance)   \
CreateWindow(ANIMATE_CLASS, NULL, dwStyle, 0, 0, 0, 0, hwndP, \
             (HMENU)(id), hInstance, NULL)

#define Animate_Open(hwnd, szName) \
SendMessage(hwnd, ACM_OPEN, 0, (LPARAM)(LPTSTR)(szName))

#define Animate_Play(hwnd, from, to, rep) \
SendMessage(hwnd, ACM_PLAY, (WPARAM)(UINT)(rep), (LPARAM)MAKELONG(from, to))

#define Animate_Stop(hwnd) \
SendMessage(hwnd, ACM_STOP, 0, 0)

#define Animate_Close(hwnd) \
Animate_Open(hwnd, NULL)

#define Animate_Seek(hwnd, frame) \
Animate_Play(hwnd, frame, frame, 1)

/* Property sheet macros */

#define PropSheet_AddPage(hPropSheetDlg, hpage) \
SendMessage(hPropSheetDlg, PSM_ADDPAGE, 0, (LPARAM)(HPROPSHEETPAGE)hpage)

#define PropSheet_Apply(hPropSheetDlg) \
SendMessage(hPropSheetDlg, PSM_APPLY, 0, 0)

#define PropSheet_CancelToClose(hPropSheetDlg) \
SendMessage(hPropSheetDlg, PSM_CANCELTOCLOSE, 0, 0)

#define PropSheet_Changed(hPropSheetDlg, hwndPage) \
SendMessage(hPropSheetDlg, PSM_CHANGED, (WPARAM)(HWND)hwndPage, 0)

#define PropSheet_GetCurrentPageHwnd(hDlg) \
SendMessage(hDlg, PSM_GETCURRENTPAGEHWND, 0, 0)

#define PropSheet_GetTabControl(hPropSheetDlg) \
SendMessage(hPropSheetDlg, PSM_GETTABCONTROL, 0, 0)

#define PropSheet_IsDialogMessage(hDlg, pMsg) \
SendMessage(hDlg, PSM_ISDIALOGMESSAGE, 0, (LPARAM)pMsg)

#define PropSheet_PressButton(hPropSheetDlg, iButton) \
SendMessage(hPropSheetDlg, PSM_PRESSBUTTON, (WPARAM)(int)iButton, 0)

#define PropSheet_QuerySiblings(hPropSheetDlg, param1, param2) \
SendMessage(hPropSheetDlg, PSM_QUERYSIBLINGS, (WPARAM)param1, (LPARAM)param2)

#define PropSheet_RebootSystem(hPropSheetDlg) \
SendMessage(hPropSheetDlg, PSM_REBOOTSYSTEM, 0, 0)

#define PropSheet_RemovePage(hPropSheetDlg, index, hpage) \
SendMessage(hPropSheetDlg, PSM_REMOVEPAGE, (WPARAM)(int)index, \
	    (LPARAM)(HPROPSHEETPAGE)hpage)

#define PropSheet_RestartWindows(hPropSheetDlg) \
SendMessage(hPropSheetDlg, PSM_RESTARTWINDOWS, 0, 0)

#define PropSheet_SetCurSel(hPropSheetDlg, hpage, index) \
SendMessage(hPropSheetDlg, PSM_SETCURSEL, (WPARAM)(int)index, \
	    (LPARAM)(HPROPSHEETPAGE)hpage)

#define PropSheet_SetCurSelByID(hPropSheetDlg, id) \
SendMessage(hPropSheetDlg, PSM_SETCURSELID, 0, (LPARAM)(int)id)

#define PropSheet_SetFinishText(hPropSheetDlg, lpszText) \
SendMessage(hPropSheetDlg, PSM_SETFINISHTEXT, 0, (LPARAM)(LPTSTR)lpszText)

#define PropSheet_SetTitle(hPropSheetDlg, dwStyle, lpszText) \
SendMessage(hPropSheetDlg, PSM_SETTITLE, (WPARAM)(DWORD)dwStyle, \
	    (LPARAM)(LPCTSTR)lpszText)

#define PropSheet_SetWizButtons(hPropSheetDlg, dwFlags) \
SendMessage(hPropSheetDlg, PSM_SETWIZBUTTONS, 0, (LPARAM)(DWORD)dwFlags)

#define PropSheet_UnChanged(hPropSheetDlg, hwndPage) \
SendMessage(hPropSheetDlg, PSM_UNCHANGED, (WPARAM)(HWND)hwndPage, 0)

/* Header control */
#define Header_DeleteItem(hwndHD, index)     \
      (WINBOOL)SendMessage((hwndHD), HDM_DELETEITEM, (WPARAM)(int)(index), 0L)  

#define Header_GetItem(hwndHD, index, phdi)      \
    (WINBOOL)SendMessage((hwndHD), HDM_GETITEM,   \
    (WPARAM)(int)(index), (LPARAM)(HD_ITEM FAR*)(phdi))
 
#define Header_GetItemCount(hwndHD)   \
       (int)SendMessage((hwndHD), HDM_GETITEMCOUNT, 0, 0L)

#define Header_InsertItem(hwndHD, index, phdi) \
    (int)SendMessage((hwndHD), HDM_INSERTITEM, (WPARAM)(int)(index), \
    (LPARAM)(const HD_ITEM FAR*)(phdi))
  
#define Header_Layout(hwndHD, playout) \
    (WINBOOL)SendMessage((hwndHD), HDM_LAYOUT, 0, \
    (LPARAM)(HD_LAYOUT FAR*)(playout))
  
#define Header_SetItem(hwndHD, index, phdi) \
    (WINBOOL)SendMessage((hwndHD), HDM_SETITEM,  \
    (WPARAM)(int)(index), (LPARAM)(const HD_ITEM FAR*)(phdi))

/* List View */
#define ListView_Arrange(hwndLV, code) \
SendMessage((hwndLV), LVM_ARRANGE, (WPARAM)(UINT)(code), 0)

#define ListView_CreateDragImage(hwnd, i, lpptUpLeft) \
SendMessage((hwnd), LVM_CREATEDRAGIMAGE, (WPARAM)(int)(i), \
	    (LPARAM)(LPPOINT)(lpptUpLeft))

#define ListView_DeleteAllItems(hwnd) \
SendMessage(hwnd, LVM_DELETEALLITEMS, 0, 0)

#define ListView_DeleteColumn(hwnd, iCol) \
SendMessage((hwnd), LVM_DELETECOLUMN, (WPARAM)(int)(iCol), 0)

#define ListView_DeleteItem(hwnd, iItem) \
SendMessage(hwnd, LVM_DELETEITEM, (WPARAM)(int)iItem, 0)

#define ListView_EditLabel(hwndLV, i) \
SendMessage((hwndLV), LVM_EDITLABEL, (WPARAM)(int)i, 0)

#define ListView_EnsureVisible(hwndLV, i, fPartialOK) \
SendMessage(hwndLV, LVM_ENSUREVISIBLE, (WPARAM)(int)i, \
	    MAKELPARAM((fPartialOK), 0))

#define ListView_FindItem(hwnd, iStart, plvfi) \
SendMessage(hwnd, LVM_FINDITEM, (WPARAM)(int)iStart, \
	    (LPARAM)(const LV_FINDINFO *)plvfi)

#define ListView_GetBkColor(hwnd) \
SendMessage((HWND)hwnd, LVM_GETBKCOLOR, 0, 0)

#define ListView_GetCallbackMask(hwnd) \
SendMessage(hwnd, LVM_GETCALLBACKMASK, 0, 0)

#define ListView_GetColumn(hwnd, iCol, pcol) \
SendMessage((hwnd), LVM_GETCOLUMN, (WPARAM)(int)(iCol), \
	    (LPARAM)(LV_COLUMN *)(pcol))

#define ListView_GetColumnWidth(hwnd, iCol) \
SendMessage((hwnd), LVM_GETCOLUMNWIDTH, (WPARAM)(int)(iCol), 0)

#define ListView_GetCountPerPage(hwndLV) \
SendMessage((hwndLV), LVM_GETCOUNTPERPAGE, 0, 0)

#define ListView_GetEditControl(hwndLV) \
SendMessage((hwndLV), LVM_GETEDITCONTROL, 0, 0)

#define ListView_GetImageList(hwnd, iImageList) \
SendMessage(hwnd, LVM_GETIMAGELIST, (WPARAM)(INT)iImageList, 0)

#define ListView_GetISearchString(hwndLV, lpsz) \
SendMessage((hwndLV), LVM_GETISEARCHSTRING, 0, (LPARAM)(LPTSTR)lpsz)

#define ListView_GetItem(hwnd, pitem) \
SendMessage(hwnd, LVM_GETITEM, 0, (LPARAM)(LV_ITEM *)(pitem))

#define ListView_GetItemCount(hwnd) \
SendMessage(hwnd, LVM_GETITEMCOUNT, 0, 0)

#define ListView_GetItemPosition(hwndLV, i, ppt) \
SendMessage(hwndLV, LVM_GETITEMPOSITION, (WPARAM)(int)i, \
	    (LPARAM)(POINT *)ppt)

#define ListView_GetItemRect(hwnd, i, prc, code) \
SendMessage(hwnd, LVM_GETITEMRECT, (WPARAM)(int)i, \
           ((prc) ? (((RECT *)(prc))->left = (code), \
		     (LPARAM)(RECT *)(prc)) : (LPARAM)(RECT *)NULL))

#define ListView_GetItemSpacing(hwndLV, fSmall) \
SendMessage((hwndLV), LVM_GETITEMSPACING, fSmall, 0)

#define ListView_GetItemState(hwndLV, i, mask) \
SendMessage((hwndLV), LVM_GETITEMSTATE, (WPARAM)i, (LPARAM)mask)

#define ListView_GetItemText(hwndLV, i, iSubItem_, pszText_, cchTextMax_) \
{ LV_ITEM _gnu_lvi;\
  _gnu_lvi.iSubItem = iSubItem_;\
  _gnu_lvi.cchTextMax = cchTextMax_;\
  _gnu_lvi.pszText = pszText_;\
  SendMessage((hwndLV), LVM_GETITEMTEXT, (WPARAM)i, \
	      (LPARAM)(LV_ITEM *)&_gnu_lvi) {}\
}

#define ListView_GetNextItem(hwnd, iStart, flags) \
SendMessage(hwnd, LVM_GETNEXTITEM, (WPARAM)(int)iStart, (LPARAM)flags)

#define ListView_GetOrigin(hwndLV, ppt) \
SendMessage((hwndLV), LVM_GETORIGIN, (WPARAM)0, (LPARAM)(POINT *)(ppt))

#define ListView_GetSelectedCount(hwndLV) \
SendMessage((hwndLV), LVM_GETSELECTEDCOUNT, 0, 0)

#define ListView_GetStringWidth(hwndLV, psz) \
SendMessage(hwndLV, LVM_GETSTRINGWIDTH, 0, (LPARAM)(LPCTSTR)psz)

#define ListView_GetTextBkColor(hwnd)  \
SendMessage((hwnd), LVM_GETTEXTBKCOLOR, 0, 0)

#define ListView_GetTextColor(hwnd)  \
SendMessage((hwnd), LVM_GETTEXTCOLOR, 0, 0)

#define ListView_GetTopIndex(hwndLV) \
SendMessage((hwndLV), LVM_GETTOPINDEX, 0, 0)

#define ListView_GetViewRect(hwnd, prc) \
SendMessage((hwnd), LVM_GETVIEWRECT, 0, (LPARAM)(RECT *)(prc))

#define ListView_HitTest(hwndLV, pinfo) \
SendMessage(hwndLV, LVM_HITTEST, 0, (LPARAM)(LV_HITTESTINFO *)pinfo)

#define ListView_InsertColumn(hwnd, iCol, pcol) \
SendMessage((hwnd), LVM_INSERTCOLUMN, (WPARAM)(int)(iCol), \
	    (LPARAM)(const LV_COLUMN *)(pcol))

#define ListView_InsertItem(hwnd, pitem) \
SendMessage(hwnd, LVM_INSERTITEM, 0, (LPARAM)(const LV_ITEM *)pitem)

#define ListView_RedrawItems(hwndLV, iFirst, iLast) \
SendMessage((hwndLV), LVM_REDRAWITEMS, (WPARAM)(int)iFirst, (LPARAM)(int)iLast)

#define ListView_Scroll(hwndLV, dx, dy) \
SendMessage((hwndLV), LVM_SCROLL, (WPARAM)(int)dx, (LPARAM)(int)dy)

#define ListView_SetBkColor(hwnd, clrBk) \
SendMessage(hwnd, LVM_SETBKCOLOR, 0, (LPARAM)(COLORREF)clrBk)

#define ListView_SetCallbackMask(hwnd, mask) \
SendMessage(hwnd, LVM_SETCALLBACKMASK, (WPARAM)(UINT)(mask), 0)

#define ListView_SetColumn(hwnd, iCol, pcol) \
SendMessage((hwnd), LVM_SETCOLUMN, (WPARAM)(int)(iCol), \
	    (LPARAM)(const LV_COLUMN *)(pcol))

#define ListView_SetColumnWidth(hwnd, iCol, cx) \
SendMessage((hwnd), LVM_SETCOLUMNWIDTH, (WPARAM)(int)(iCol), \
	    MAKELPARAM((cx), 0))


#define ListView_SetImageList(hwnd, himl, iImageList) \
SendMessage(hwnd, LVM_SETIMAGELIST, (WPARAM)(iImageList), \
	    (LPARAM)(UINT)(HIMAGELIST)(himl))

#define ListView_SetItem(hwnd, pitem) \
SendMessage(hwnd, LVM_SETITEM, 0, (LPARAM)(const LV_ITEM *)pitem)

#define ListView_SetItemCount(hwndLV, cItems) \
SendMessage((hwndLV), LVM_SETITEMCOUNT, (WPARAM)cItems, 0)

#define ListView_SetItemPosition(hwndLV, i, x, y) \
SendMessage(hwndLV, LVM_SETITEMPOSITION, (WPARAM)(int)(i), \
	    MAKELPARAM((x), (y)))

#define ListView_SetItemPosition32(hwndLV, i, x, y) \
{ POINT ptNewPos = {x,y}; \
    SendMessage((hwndLV), LVM_SETITEMPOSITION32, (WPARAM)(int)(i), \
		(LPARAM)&ptNewPos) {} \
}

#define ListView_SetItemState(hwndLV, i, data, mask) \
{ LV_ITEM _gnu_lvi;\
  _gnu_lvi.stateMask = mask;\
  _gnu_lvi.state = data;\
  SendMessage((hwndLV), LVM_SETITEMSTATE, (WPARAM)i, \
	      (LPARAM)(LV_ITEM *)&_gnu_lvi) {}\
}

#define ListView_SetItemText(hwndLV, i, iSubItem_, pszText_) \
{ LV_ITEM _gnu_lvi;\
  _gnu_lvi.iSubItem = iSubItem_;\
  _gnu_lvi.pszText = pszText_;\
  SendMessage((hwndLV), LVM_SETITEMTEXT, (WPARAM)i, \
	      (LPARAM)(LV_ITEM *)&_gnu_lvi) {}\
}

#define ListView_SetTextBkColor(hwnd, clrTextBk) \
SendMessage((hwnd), LVM_SETTEXTBKCOLOR, 0, (LPARAM)(COLORREF)(clrTextBk))

#define ListView_SetTextColor(hwnd, clrText) \
SendMessage((hwnd), LVM_SETTEXTCOLOR, 0, (LPARAM)(COLORREF)(clrText))

#define ListView_SortItems(hwndLV, _pfnCompare, _lPrm) \
SendMessage((hwndLV), LVM_SORTITEMS, (WPARAM)(LPARAM)_lPrm, \
	    (LPARAM)(PFNLVCOMPARE)_pfnCompare)

#define ListView_Update(hwndLV, i) \
SendMessage((hwndLV), LVM_UPDATE, (WPARAM)i, 0)

/* Tree View */
#define TreeView_InsertItem(hwnd, lpis) \
SendMessage((hwnd), TVM_INSERTITEM, 0, (LPARAM)(LPTV_INSERTSTRUCT)(lpis))

#define TreeView_DeleteItem(hwnd, hitem) \
SendMessage((hwnd), TVM_DELETEITEM, 0, (LPARAM)(HTREEITEM)(hitem))

#define TreeView_DeleteAllItems(hwnd) \
SendMessage((hwnd), TVM_DELETEITEM, 0, (LPARAM)TVI_ROOT)

#define TreeView_Expand(hwnd, hitem, code) \
SendMessage((hwnd), TVM_EXPAND, (WPARAM)code, (LPARAM)(HTREEITEM)(hitem))

#define TreeView_GetItemRect(hwnd, hitem, prc, code) \
SendMessage((hwnd), TVM_GETITEMRECT, (WPARAM)(code), (LPARAM)(RECT *)(prc)))

#define TreeView_GetCount(hwnd) \
SendMessage((hwnd), TVM_GETCOUNT, 0, 0)

#define TreeView_GetIndent(hwnd) \
SendMessage((hwnd), TVM_GETINDENT, 0, 0)

#define TreeView_SetIndent(hwnd, indent) \
SendMessage((hwnd), TVM_SETINDENT, (WPARAM)indent, 0)

#define TreeView_GetImageList(hwnd, iImage) \
SendMessage((hwnd), TVM_GETIMAGELIST, iImage, 0)

#define TreeView_SetImageList(hwnd, himl, iImage) \
SendMessage((hwnd), TVM_SETIMAGELIST, iImage, (LPARAM)(UINT)(HIMAGELIST)(himl))

#define TreeView_GetNextItem(hwnd, hitem, code) \
SendMessage((hwnd), TVM_GETNEXTITEM, (WPARAM)code, (LPARAM)(HTREEITEM)(hitem))

#define TreeView_GetChild(hwnd, hitem) \
TreeView_GetNextItem(hwnd, hitem, TVGN_CHILD)

#define TreeView_GetNextSibling(hwnd, hitem) \
TreeView_GetNextItem(hwnd, hitem, TVGN_NEXT)

#define TreeView_GetPrevSibling(hwnd, hitem) \
TreeView_GetNextItem(hwnd, hitem, TVGN_PREVIOUS)

#define TreeView_GetParent(hwnd, hitem) \
TreeView_GetNextItem(hwnd, hitem, TVGN_PARENT)

#define TreeView_GetFirstVisible(hwnd) \
TreeView_GetNextItem(hwnd, NULL,  TVGN_FIRSTVISIBLE)

#define TreeView_GetNextVisible(hwnd, hitem) \
TreeView_GetNextItem(hwnd, hitem, TVGN_NEXTVISIBLE)

#define TreeView_GetPrevVisible(hwnd, hitem) \
TreeView_GetNextItem(hwnd, hitem, TVGN_PREVIOUSVISIBLE)

#define TreeView_GetSelection(hwnd) \
TreeView_GetNextItem(hwnd, NULL,  TVGN_CARET)

#define TreeView_GetDropHilight(hwnd) \
TreeView_GetNextItem(hwnd, NULL,  TVGN_DROPHILITE)

#define TreeView_GetRoot(hwnd) \
TreeView_GetNextItem(hwnd, NULL,  TVGN_ROOT)

#define TreeView_Select(hwnd, hitem, code) \
SendMessage((hwnd), TVM_SELECTITEM, (WPARAM)code, (LPARAM)(HTREEITEM)(hitem))


#define TreeView_SelectItem(hwnd, hitem) \
TreeView_Select(hwnd, hitem, TVGN_CARET)

#define TreeView_SelectDropTarget(hwnd, hitem) \
TreeView_Select(hwnd, hitem, TVGN_DROPHILITE)

#define TreeView_SelectSetFirstVisible(hwnd, hitem) \
TreeView_Select(hwnd, hitem, TVGN_FIRSTVISIBLE)

#define TreeView_GetItem(hwnd, pitem) \
SendMessage((hwnd), TVM_GETITEM, 0, (LPARAM)(TV_ITEM *)(pitem))

#define TreeView_SetItem(hwnd, pitem) \
SendMessage((hwnd), TVM_SETITEM, 0, (LPARAM)(const TV_ITEM *)(pitem))

#define TreeView_EditLabel(hwnd, hitem) \
SendMessage((hwnd), TVM_EDITLABEL, 0, (LPARAM)(HTREEITEM)(hitem))

#define TreeView_GetEditControl(hwnd) \
SendMessage((hwnd), TVM_GETEDITCONTROL, 0, 0)

#define TreeView_GetVisibleCount(hwnd) \
SendMessage((hwnd), TVM_GETVISIBLECOUNT, 0, 0)

#define TreeView_HitTest(hwnd, lpht) \
SendMessage((hwnd), TVM_HITTEST, 0, (LPARAM)(LPTV_HITTESTINFO)(lpht))

#define TreeView_CreateDragImage(hwnd, hitem) \
SendMessage((hwnd), TVM_CREATEDRAGIMAGE, 0, (LPARAM)(HTREEITEM)(hitem))

#define TreeView_SortChildren(hwnd, hitem, recurse) \
SendMessage((hwnd), TVM_SORTCHILDREN, (WPARAM)recurse, \
            (LPARAM)(HTREEITEM)(hitem))

#define TreeView_EnsureVisible(hwnd, hitem) \
SendMessage((hwnd), TVM_ENSUREVISIBLE, 0, (LPARAM)(HTREEITEM)(hitem))

#define TreeView_SortChildrenCB(hwnd, psort, recurse) \
SendMessage((hwnd), TVM_SORTCHILDRENCB, (WPARAM)recurse, \
            (LPARAM)(LPTV_SORTCB)(psort))

#define TreeView_EndEditLabelNow(hwnd, fCancel) \
SendMessage((hwnd), TVM_ENDEDITLABELNOW, (WPARAM)fCancel, 0)

#define TreeView_GetISearchString(hwndTV, lpsz) \
SendMessage((hwndTV), TVM_GETISEARCHSTRING, 0, (LPARAM)(LPTSTR)lpsz)


/* Tab control */
#define TabCtrl_GetImageList(hwnd) \
SendMessage((hwnd), TCM_GETIMAGELIST, 0, 0)

#define TabCtrl_SetImageList(hwnd, himl) \
SendMessage((hwnd), TCM_SETIMAGELIST, 0, (LPARAM)(UINT)(HIMAGELIST)(himl))

#define TabCtrl_GetItemCount(hwnd) \
SendMessage((hwnd), TCM_GETITEMCOUNT, 0, 0)

#define TabCtrl_GetItem(hwnd, iItem, pitem) \
SendMessage((hwnd), TCM_GETITEM, (WPARAM)(int)iItem, \
            (LPARAM)(TC_ITEM *)(pitem))

#define TabCtrl_SetItem(hwnd, iItem, pitem) \
SendMessage((hwnd), TCM_SETITEM, (WPARAM)(int)iItem, \
            (LPARAM)(TC_ITEM *)(pitem))

#define TabCtrl_InsertItem(hwnd, iItem, pitem)   \
SendMessage((hwnd), TCM_INSERTITEM, (WPARAM)(int)iItem, \
            (LPARAM)(const TC_ITEM *)(pitem))

#define TabCtrl_DeleteItem(hwnd, i) \
SendMessage((hwnd), TCM_DELETEITEM, (WPARAM)(int)(i), 0)

#define TabCtrl_DeleteAllItems(hwnd) \
SendMessage((hwnd), TCM_DELETEALLITEMS, 0, 0)

#define TabCtrl_GetItemRect(hwnd, i, prc) \
SendMessage((hwnd), TCM_GETITEMRECT, (WPARAM)(int)(i), (LPARAM)(RECT *)(prc))

#define TabCtrl_GetCurSel(hwnd) \
SendMessage((hwnd), TCM_GETCURSEL, 0, 0)

#define TabCtrl_SetCurSel(hwnd, i) \
SendMessage((hwnd), TCM_SETCURSEL, (WPARAM)i, 0)

#define TabCtrl_HitTest(hwndTC, pinfo) \
SendMessage((hwndTC), TCM_HITTEST, 0, (LPARAM)(TC_HITTESTINFO *)(pinfo))

#define TabCtrl_SetItemExtra(hwndTC, cb) \
SendMessage((hwndTC), TCM_SETITEMEXTRA, (WPARAM)(cb), 0)

#define TabCtrl_AdjustRect(hwnd, bLarger, prc) \
SendMessage(hwnd, TCM_ADJUSTRECT, (WPARAM)(WINBOOL)bLarger, \
            (LPARAM)(RECT *)prc)

#define TabCtrl_SetItemSize(hwnd, x, y) \
SendMessage((hwnd), TCM_SETITEMSIZE, 0, MAKELPARAM(x,y))

#define TabCtrl_RemoveImage(hwnd, i) \
SendMessage((hwnd), TCM_REMOVEIMAGE, i, 0)

#define TabCtrl_SetPadding(hwnd,  cx, cy) \
SendMessage((hwnd), TCM_SETPADDING, 0, MAKELPARAM(cx, cy))

#define TabCtrl_GetRowCount(hwnd) \
SendMessage((hwnd), TCM_GETROWCOUNT, 0, 0)

#define TabCtrl_GetToolTips(hwnd) \
SendMessage((hwnd), TCM_GETTOOLTIPS, 0, 0)

#define TabCtrl_SetToolTips(hwnd, hwndTT) \
SendMessage((hwnd), TCM_SETTOOLTIPS, (WPARAM)hwndTT, 0)

#define TabCtrl_GetCurFocus(hwnd) \
SendMessage((hwnd), TCM_GETCURFOCUS, 0, 0)

#define TabCtrl_SetCurFocus(hwnd, i) \
SendMessage((hwnd),TCM_SETCURFOCUS, i, 0)

#define CommDlg_OpenSave_GetSpecA(_hdlg, _psz, _cbmax) \
SNDMSG(_hdlg, CDM_GETSPEC, (WPARAM)_cbmax, (LPARAM)(LPSTR)_psz)

#define CommDlg_OpenSave_GetSpecW(_hdlg, _psz, _cbmax) \
SNDMSG(_hdlg, CDM_GETSPEC, (WPARAM)_cbmax, (LPARAM)(LPWSTR)_psz)

#ifdef UNICODE
#define CommDlg_OpenSave_GetSpec  CommDlg_OpenSave_GetSpecW
#else
#define CommDlg_OpenSave_GetSpec  CommDlg_OpenSave_GetSpecA
#endif /* !UNICODE */

#define CommDlg_OpenSave_GetFilePathA(_hdlg, _psz, _cbmax) \
SNDMSG(_hdlg, CDM_GETFILEPATH, (WPARAM)_cbmax, (LPARAM)(LPSTR)_psz)

#define CommDlg_OpenSave_GetFilePathW(_hdlg, _psz, _cbmax) \
SNDMSG(_hdlg, CDM_GETFILEPATH, (WPARAM)_cbmax, (LPARAM)(LPWSTR)_psz)

#ifdef UNICODE
#define CommDlg_OpenSave_GetFilePath  CommDlg_OpenSave_GetFilePathW
#else
#define CommDlg_OpenSave_GetFilePath  CommDlg_OpenSave_GetFilePathA
#endif /* !UNICODE */

#define CommDlg_OpenSave_GetFolderPathA(_hdlg, _psz, _cbmax) \
SNDMSG(_hdlg, CDM_GETFOLDERPATH, (WPARAM)_cbmax, (LPARAM)(LPSTR)_psz)

#define CommDlg_OpenSave_GetFolderPathW(_hdlg, _psz, _cbmax) \
SNDMSG(_hdlg, CDM_GETFOLDERPATH, (WPARAM)_cbmax, (LPARAM)(LPWSTR)_psz)

#ifdef UNICODE
#define CommDlg_OpenSave_GetFolderPath  CommDlg_OpenSave_GetFolderPathW
#else
#define CommDlg_OpenSave_GetFolderPath  CommDlg_OpenSave_GetFolderPathA
#endif /* !UNICODE */

#define CommDlg_OpenSave_GetFolderIDList(_hdlg, _pidl, _cbmax) \
SNDMSG(_hdlg, CDM_GETFOLDERIDLIST, (WPARAM)_cbmax, (LPARAM)(LPVOID)_pidl)

#define CommDlg_OpenSave_SetControlText(_hdlg, _id, _text) \
SNDMSG(_hdlg, CDM_SETCONTROLTEXT, (WPARAM)_id, (LPARAM)(LPSTR)_text)

#define CommDlg_OpenSave_HideControl(_hdlg, _id) \
SNDMSG(_hdlg, CDM_HIDECONTROL, (WPARAM)_id, 0)

#define CommDlg_OpenSave_SetDefExt(_hdlg, _pszext) \
SNDMSG(_hdlg, CDM_SETDEFEXT, 0, (LPARAM)(LPSTR)_pszext)

LONG
STDCALL
RegCloseKey (
    HKEY hKey
    ) {}

LONG
STDCALL
RegSetKeySecurity (
    HKEY hKey,
    SECURITY_INFORMATION SecurityInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor
    ) {}

LONG
STDCALL
RegFlushKey (
    HKEY hKey
    ) {}

LONG
STDCALL
RegGetKeySecurity (
    HKEY hKey,
    SECURITY_INFORMATION SecurityInformation,
    PSECURITY_DESCRIPTOR pSecurityDescriptor,
    LPDWORD lpcbSecurityDescriptor
    ) {}

LONG
STDCALL
RegNotifyChangeKeyValue (
    HKEY hKey,
    WINBOOL bWatchSubtree,
    DWORD dwNotifyFilter,
    HANDLE hEvent,
    WINBOOL fAsynchronus
    ) {}

WINBOOL
STDCALL
IsValidCodePage(
    UINT  CodePage) {}


UINT
STDCALL
GetACP(void) {}


UINT
STDCALL
GetOEMCP(void) {}


WINBOOL
STDCALL
GetCPInfo(UINT v, LPCPINFO info) {}


WINBOOL
STDCALL
IsDBCSLeadByte(
    BYTE  TestChar) {}


WINBOOL
STDCALL
IsDBCSLeadByteEx(
    UINT  CodePage,
    BYTE  TestChar) {}


int
STDCALL
MultiByteToWideChar(
    UINT     CodePage,
    DWORD    dwFlags,
    LPCSTR   lpMultiByteStr,
    int      cchMultiByte,
    LPWSTR   lpWideCharStr,
    int      cchWideChar) {}


int
STDCALL
WideCharToMultiByte(
    UINT     CodePage,
    DWORD    dwFlags,
    LPCWSTR  lpWideCharStr,
    int      cchWideChar,
    LPSTR    lpMultiByteStr,
    int      cchMultiByte,
    LPCSTR   lpDefaultChar,
    LPBOOL   lpUsedDefaultChar) {}

WINBOOL
STDCALL
IsValidLocale(
    LCID   Locale,
    DWORD  dwFlags) {}


LCID
STDCALL
ConvertDefaultLocale(
    LCID   Locale) {}


LCID
STDCALL
GetThreadLocale(void) {}


WINBOOL
STDCALL
SetThreadLocale(
    LCID  Locale
    ) {}


LANGID
STDCALL
GetSystemDefaultLangID(void) {}


LANGID
STDCALL
GetUserDefaultLangID(void) {}


LCID
STDCALL
GetSystemDefaultLCID(void) {}


LCID
STDCALL
GetUserDefaultLCID(void) {}


WINBOOL
STDCALL
ReadConsoleOutputAttribute(
    HANDLE hConsoleOutput,
    LPWORD lpAttribute,
    DWORD nLength,
    COORD dwReadCoord,
    LPDWORD lpNumberOfAttrsRead
    ) {}


WINBOOL
STDCALL
WriteConsoleOutputAttribute(
    HANDLE hConsoleOutput,
    CONST WORD *lpAttribute,
    DWORD nLength,
    COORD dwWriteCoord,
    LPDWORD lpNumberOfAttrsWritten
    ) {}


WINBOOL
STDCALL
FillConsoleOutputAttribute(
    HANDLE hConsoleOutput,
    WORD   wAttribute,
    DWORD  nLength,
    COORD  dwWriteCoord,
    LPDWORD lpNumberOfAttrsWritten
    ) {}


WINBOOL
STDCALL
GetConsoleMode(
    HANDLE hConsoleHandle,
    LPDWORD lpMode
    ) {}


WINBOOL
STDCALL
GetNumberOfConsoleInputEvents(
    HANDLE hConsoleInput,
    LPDWORD lpNumberOfEvents
    ) {}


WINBOOL
STDCALL
GetConsoleScreenBufferInfo(
    HANDLE hConsoleOutput,
    PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo
    ) {}


COORD
STDCALL
GetLargestConsoleWindowSize(
    HANDLE hConsoleOutput
    ) {}


WINBOOL
STDCALL
GetConsoleCursorInfo(
    HANDLE hConsoleOutput,
    PCONSOLE_CURSOR_INFO lpConsoleCursorInfo
    ) {}


WINBOOL
STDCALL
GetNumberOfConsoleMouseButtons(
    LPDWORD lpNumberOfMouseButtons
    ) {}


WINBOOL
STDCALL
SetConsoleMode(
    HANDLE hConsoleHandle,
    DWORD dwMode
    ) {}


WINBOOL
STDCALL
SetConsoleActiveScreenBuffer(
    HANDLE hConsoleOutput
    ) {}


WINBOOL
STDCALL
FlushConsoleInputBuffer(
    HANDLE hConsoleInput
    ) {}


WINBOOL
STDCALL
SetConsoleScreenBufferSize(
    HANDLE hConsoleOutput,
    COORD dwSize
    ) {}


WINBOOL
STDCALL
SetConsoleCursorPosition(
    HANDLE hConsoleOutput,
    COORD dwCursorPosition
    ) {}


WINBOOL
STDCALL
SetConsoleCursorInfo(
    HANDLE hConsoleOutput,
    CONST CONSOLE_CURSOR_INFO *lpConsoleCursorInfo
    ) {}

WINBOOL
STDCALL
SetConsoleWindowInfo(
    HANDLE hConsoleOutput,
    WINBOOL bAbsolute,
    CONST SMALL_RECT *lpConsoleWindow
    ) {}


WINBOOL
STDCALL
SetConsoleTextAttribute(
    HANDLE hConsoleOutput,
    WORD wAttributes
    ) {}


WINBOOL
STDCALL
SetConsoleCtrlHandler(
    PHANDLER_ROUTINE HandlerRoutine,
    WINBOOL Add
    ) {}


WINBOOL
STDCALL
GenerateConsoleCtrlEvent(
    DWORD dwCtrlEvent,
    DWORD dwProcessGroupId
    ) {}


WINBOOL
STDCALL
AllocConsole( VOID ) {}


WINBOOL
STDCALL
FreeConsole( VOID ) {}



HANDLE
STDCALL
CreateConsoleScreenBuffer(
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    CONST SECURITY_ATTRIBUTES *lpSecurityAttributes,
    DWORD dwFlags,
    LPVOID lpScreenBufferData
    ) {}


UINT
STDCALL
GetConsoleCP( VOID ) {}


WINBOOL
STDCALL
SetConsoleCP(
    UINT wCodePageID
    ) {}


UINT
STDCALL
GetConsoleOutputCP( VOID ) {}


WINBOOL
STDCALL
SetConsoleOutputCP(
    UINT wCodePageID
    ) {}

DWORD STDCALL
WNetConnectionDialog(
    HWND  hwnd,
    DWORD dwType
    ) {}

DWORD STDCALL
WNetDisconnectDialog(
    HWND  hwnd,
    DWORD dwType
    ) {}

DWORD STDCALL
WNetCloseEnum(
    HANDLE   hEnum
    ) {}

WINBOOL
STDCALL
CloseServiceHandle(
    SC_HANDLE   hSCObject
    ) {}


WINBOOL
STDCALL
ControlService(
    SC_HANDLE           hService,
    DWORD               dwControl,
    LPSERVICE_STATUS    lpServiceStatus
    ) {}

WINBOOL
STDCALL
DeleteService(
    SC_HANDLE   hService
    ) {}

SC_LOCK
STDCALL
LockServiceDatabase(
    SC_HANDLE   hSCManager
    ) {}


WINBOOL
STDCALL
NotifyBootConfigStatus(
    WINBOOL     BootAcceptable
    ) {}

WINBOOL
STDCALL
QueryServiceObjectSecurity(
    SC_HANDLE               hService,
    SECURITY_INFORMATION    dwSecurityInformation,
    PSECURITY_DESCRIPTOR    lpSecurityDescriptor,
    DWORD                   cbBufSize,
    LPDWORD                 pcbBytesNeeded
    ) {}


WINBOOL
STDCALL
QueryServiceStatus(
    SC_HANDLE           hService,
    LPSERVICE_STATUS    lpServiceStatus
    ) {}

WINBOOL
STDCALL
SetServiceObjectSecurity(
    SC_HANDLE               hService,
    SECURITY_INFORMATION    dwSecurityInformation,
    PSECURITY_DESCRIPTOR    lpSecurityDescriptor
    ) {}


WINBOOL
STDCALL
SetServiceStatus(
    SERVICE_STATUS_HANDLE   hServiceStatus,
    LPSERVICE_STATUS        lpServiceStatus
    ) {}

WINBOOL
STDCALL
UnlockServiceDatabase(
    SC_LOCK     ScLock
    ) {}


/* shellapi.h */

void
WINAPI
DragAcceptFiles (
	HWND hWnd,
	WINBOOL b
	) {}


void
WINAPI
DragFinish (
	HDROP hDrop
	) {}


WINBOOL
WINAPI
DragQueryPoint (
	HDROP hDrop,
	LPPOINT pt
	) {}


HICON
WINAPI
DuplicateIcon (
	HINSTANCE hInst,
	HICON hIcon
	) {}


/* ddeml.h */

HCONV WINAPI	DdeConnect (DWORD d1, HSZ hSz, HSZ hSz1, CONVCONTEXT *context) {}
WINBOOL WINAPI	DdeDisconnect (HCONV hConv) {}
WINBOOL WINAPI	DdeFreeDataHandle (HDDEDATA hDde) {}
DWORD WINAPI	DdeGetData (HDDEDATA hDde, BYTE *p1, DWORD d1, DWORD d2) {}
UINT WINAPI	DdeGetLastError (DWORD d) {}
HDDEDATA WINAPI	DdeNameService (DWORD d, HSZ hSz1, HSZ hSz2, UINT v) {}
WINBOOL WINAPI	DdePostAdvise (DWORD d, HSZ hSz1, HSZ hSz2) {}
HCONV WINAPI	DdeReconnect (HCONV hConv) {}
WINBOOL WINAPI	DdeUninitialize (DWORD d) {}
int WINAPI	DdeCmpStringHandles (HSZ hSz1, HSZ hSz2) {}
HDDEDATA WINAPI	DdeCreateDataHandle (DWORD d, LPBYTE pb, DWORD d2, DWORD d3,
				HSZ hSz, UINT v1, UINT v2) {}

DWORD STDCALL NetUserEnum (LPWSTR str, DWORD d1, DWORD d2,
				LPBYTE*pb, DWORD d3, LPDWORD d4,
				LPDWORD d5, LPDWORD d6) {}
DWORD STDCALL NetApiBufferFree (LPVOID ptr) {}
DWORD STDCALL NetUserGetInfo (LPWSTR s1, LPWSTR s2, DWORD d, LPBYTE pb) {}
DWORD STDCALL NetGetDCName (LPWSTR s1, LPWSTR s2, LPBYTE*pb) {}
DWORD STDCALL NetGroupEnum (LPWSTR s1, DWORD d1, LPBYTE* pb, DWORD d2, LPDWORD d3,
				LPDWORD d4, LPDWORD d5) {}
DWORD STDCALL NetLocalGroupEnum (LPWSTR s1, DWORD d1, LPBYTE* pb, DWORD d2,
				LPDWORD d3, LPDWORD d4, LPDWORD d5) {}


/* Extensions to OpenGL */

int STDCALL
ChoosePixelFormat(HDC hDc, CONST PIXELFORMATDESCRIPTOR *pxlFrmtDesc) {}	

int STDCALL
DescribePixelFormat(HDC hDc, int v1, UINT v2, LPPIXELFORMATDESCRIPTOR pxlFrmtDesc) {}

UINT STDCALL
GetEnhMetaFilePixelFormat(HENHMETAFILE hEnMetaFile, DWORD d,
			  CONST PIXELFORMATDESCRIPTOR *pxlFrmtDesc) {}

int STDCALL
GetPixelFormat(HDC hDc) {}

WINBOOL STDCALL
SetPixelFormat(HDC hDc, int v, CONST PIXELFORMATDESCRIPTOR *pxlFrmtDesc) {}

WINBOOL STDCALL
SwapBuffers(HDC hDc) {}

HGLRC STDCALL
wglCreateContext(HDC hDc) {}

HGLRC STDCALL
wglCreateLayerContext(HDC hDc, int v) {}

WINBOOL STDCALL
wglCopyContext(HGLRC hGrRc, HGLRC hGlRc1, UINT v) {}

WINBOOL STDCALL
wglDeleteContext(HGLRC hGlRc) {}

WINBOOL STDCALL
wglDescribeLayerPlane(HDC hDc, int v1, int v2, UINT v3,
		LPLAYERPLANEDESCRIPTOR playerDescr) {}

HGLRC STDCALL
wglGetCurrentContext(VOID) {}

HDC STDCALL
wglGetCurrentDC(VOID) {}

int STDCALL
wglGetLayerPaletteEntries(HDC hDc, int v1, int v2, int v3, CONST COLORREF *color) {}

PROC STDCALL
wglGetProcAddress(LPCSTR str) {}

WINBOOL STDCALL
wglMakeCurrent(HDC hDc, HGLRC hGlRc) {}

WINBOOL STDCALL
wglRealizeLayerPalette(HDC hDc, int v, WINBOOL pb) {}

int STDCALL
wglSetLayerPaletteEntries(HDC hDc, int v1, int v2, int v3, CONST COLORREF *color) {}

WINBOOL STDCALL
wglShareLists(HGLRC hGlRc1, HGLRC hGlRc2) {}

WINBOOL STDCALL
wglSwapLayerBuffers(HDC hDc, UINT v) {}

void WINAPI
SHAddToRecentDocs (UINT v, LPCVOID ptr) {}

LPITEMIDLIST WINAPI
SHBrowseForFolder (LPBROWSEINFO browseInfo) {}

void WINAPI
SHChangeNotify (LONG v1, UINT v2, LPCVOID p1, LPCVOID p2) {}

int WINAPI
SHFileOperation (LPSHFILEOPSTRUCT shFileOpStruct) {}

void WINAPI
SHFreeNameMappings (HANDLE h) {}

/* Define when SHELLFOLDER is defined.
HRESULT WINAPI
SHGetDataFromIDList (LPSHELLFOLDER shellFolder, LPCITEMIDLIST cItemidList,
		int v1, PVOID ptr, int v2) {}

HRESULT WINAPI
SHGetDesktopFolder (LPSHELLFOLDER shellFolder) {}
*/

DWORD WINAPI
SHGetFileInfo (LPCTSTR str, DWORD d, SHFILEINFO FAR *shFileInfo,
		UINT v1, UINT v2) {}

/* Define when IUnknown is defined.
HRESULT WINAPI
SHGetInstanceExplorer (IUnknown **) {}
*/

/* Define when MALLOC is defined.
HRESULT WINAPI
SHGetMalloc (LPMALLOC *) {}
*/

WINBOOL WINAPI
SHGetPathFromIDList (LPCITEMIDLIST cItemIdList, LPTSTR str) {}

HRESULT WINAPI
SHGetSpecialFolderLocation (HWND hWnd, int v, LPITEMIDLIST *itemIdList) {}

/* Define when REFCLSID is defined.
HRESULT WINAPI
SHLoadInProc (REFCLSID refClsId) {}
*/

/*
   RES added define to allow compilation of INTERACTER code
*/
typedef UINT (CALLBACK* LPFNDEVMODE)(HWND, HMODULE, LPDEVMODE, LPSTR, LPSTR, LPDEVMODE, LPSTR, UINT);

/*
   RES - Missing defines for print manager functions
*/
WINBOOL
WINAPI
ClosePrinter(
    HANDLE hPrinter
) {}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/* RC_INVOKED */

#endif /* _GNU_H_WINDOWS32_COMMONFUNCTIONS */
