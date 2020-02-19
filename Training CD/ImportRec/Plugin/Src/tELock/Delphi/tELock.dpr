// tELock.cpp : Plugin for ImpREC to find tELock0.92x real API in its wrapped code
////////////////////////////////////////////////////////////////////////////////////////////
//
// Very quick and simple example to get all values in "push [API]; ... garbage ... ;ret"
// Note that this example is not a tracer but just an opcode checker.
//
////////////////////////////////////////////////////////////////////////////////////////////
library tELock;

uses windows;


// Global variables
////////////////////////////////////////////////////////////////////////////////////////////
// None

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

function Trace(hFileMap:DWORD; dwSizeMap:DWORD; dwTimeOut:DWORD; dwToTrace:DWORD; dwExactCall:DWORD):DWORD;cdecl;
var to_trace :array[0..15] of BYTE;
    address :PDWORD;
    dwPtrOutput : PDWORD;
begin
	// Map the view of the file
	dwPtrOutput := PDWORD(MapViewOfFile(hFileMap, 6, 0, 0, 0));
	if (DWORD(dwPtrOutput) = 0) then begin
                // Can't map view
                Trace := 201;
                exit;
        end;
	// Check the size of the map file
	if (dwSizeMap < 4) then begin
                // Invalid map size
                UnmapViewOfFile(pointer(dwPtrOutput));
                CloseHandle(hFileMap);
                Trace := 203;
                exit;
        end;

	// Check if we read a valid pointer
	if (IsBadReadPtr(pointer(dwToTrace), 4)) then begin
		// Bad pointer!
                UnmapViewOfFile(pointer(dwPtrOutput));
                CloseHandle(hFileMap);
                Trace := 205;
                exit;
	end;

	movememory(addr(to_trace),pointer(dwToTrace),16);
	// We must have a "push [XXXXXXX]"
	if (to_trace[0] = $FF) and (to_trace[1] = $35) then begin
		// Get the pointer in the "push [XXXXXXX]"
		address := PDWORD(addr(to_trace[2])^);

		// Check if this pointer is valid
		if (IsBadReadPtr(pointer(address), 4)) then begin
			// Bad pointer!
                        UnmapViewOfFile(pointer(dwPtrOutput));
                        CloseHandle(hFileMap);
                        Trace := 205;
                        exit;
		end;

		// Get the value in XXXXXX and write it to the mapped file
		dwPtrOutput^ := address^;

	end;

	// OK
        UnmapViewOfFile(pointer(dwPtrOutput));
        CloseHandle(hFileMap);
        Trace := 200;
end;

exports Trace;

begin
        // Initialize all you need
end.
