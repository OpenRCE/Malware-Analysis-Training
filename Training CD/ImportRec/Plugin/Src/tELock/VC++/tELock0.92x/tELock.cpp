// tELock.cpp : Plugin for ImpREC to find tELock0.92x real API in its wrapped code
////////////////////////////////////////////////////////////////////////////////////////////
//
// Very quick and simple example to get all values in "push [API]; ... garbage ... ;ret"
// Note that this example is not a tracer but just an opcode checker.
//
////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>


#define DLLEXPORT extern "C" __declspec( dllexport )

// Exported function to use (prototypes)
////////////////////////////////////////////////////////////////////////////////////////////
DLLEXPORT DWORD Trace(DWORD hFileMap, DWORD dwSizeMap, DWORD dwTimeOut, DWORD dwToTrace,
					  DWORD dwExactCall);

// Global variables
////////////////////////////////////////////////////////////////////////////////////////////
// None

// Initialize all you need
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

// Exported function to use
//
// Parameters:
// -----------
// <hFileMap>    : HANDLE of the mapped file
// <dwSizeMap>   : Size of that mapped file
// <dwTimeOut>   : TimeOut of ImpREC in Options
// <dwToTrace>   : Pointer to trace (in VA)
// <dwExactCall> : EIP of the exact call (in VA)
//
// Returned value:
// ---------------
// Use a value greater or equal to 200. It will be shown by ImpREC if no output were created

DLLEXPORT DWORD Trace(DWORD hFileMap, DWORD dwSizeMap, DWORD dwTimeOut, DWORD dwToTrace,
					  DWORD dwExactCall)
{
	// Map the view of the file
	DWORD* dwPtrOutput = (DWORD*)MapViewOfFile((HANDLE)hFileMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
	if (!dwPtrOutput)
	{
		// Can't map view
		return (201);
	}
	// Check the size of the map file
	if (dwSizeMap < 4)
	{
		// Invalid map size
		UnmapViewOfFile((LPCVOID)dwPtrOutput);
		CloseHandle((HANDLE)hFileMap);
		return (203);
	}
	
	// Check if we read a valid pointer
	if (IsBadReadPtr((VOID*)dwToTrace, 4))
	{
		// Bad pointer!
		UnmapViewOfFile((LPCVOID)dwPtrOutput);
		CloseHandle((HANDLE)hFileMap);
		return (205);
	}

	BYTE *to_trace = (BYTE*)dwToTrace;
	// We must have a "push [XXXXXXX]"
	if (to_trace[0] == 0xFF && to_trace[1] == 0x35)
	{
		// Get the pointer in the "push [XXXXXXX]"
		DWORD address = *((DWORD*)(to_trace+2));

		// Check if this pointer is valid
		if (IsBadReadPtr((VOID*)address, 4))
		{
			// Bad pointer!
			UnmapViewOfFile((LPCVOID)dwPtrOutput);
			CloseHandle((HANDLE)hFileMap);
			return (205);
		}

		// Get the value in XXXXXX and write it to the mapped file
		*dwPtrOutput = *((DWORD*)address);
	}

	// OK
	UnmapViewOfFile((LPCVOID)dwPtrOutput);
	CloseHandle((HANDLE)hFileMap);
	return (200);
}
