// aspr.pas : Plugin for ImpREC to find asprotect 1.2x real API in its wrapped code
////////////////////////////////////////////////////////////////////////////////////////////
//
// Note that this example is not a tracer but just an opcode checker.
//
////////////////////////////////////////////////////////////////////////////////////////////
library aspr;

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

function Trace(hFileMap:DWORD; dwSizeMap:DWORD; dwTimeOut:DWORD; dwToTrace:DWORD;
               dwExactCall:DWORD) : DWORD;cdecl;
var to_trace    : array[0..15] of BYTE;
    i           : DWORD;
    val         : DWORD;
    address     : PDWORD;
    found       : BOOLEAN;
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

        //all different types of redirection code, a common one is mov eax,[xxxxxx].
        //check for this and the value at xxxxxx and try to guess it ;)
        val := 0;
        found := false;

        for i := 0 to 9 do
        begin
        if to_trace[i] = $A1 then
        begin
             //check all the possible mov eax,[xxxxxx] redirections
             address := pointer((@to_trace[i+1])^);
             val     := address^;
             //val = eax returned by redirection code. try to id emulated function
             if val = GetVersion then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'GetVersion'));
                found := true;
             end;
             if val = dword(GetCommandLineA) then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'GetCommandLineA'));
                found := true;
             end;
             if val = GetCurrentProcess then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'GetCurrentProcess'));
                found := true;
             end;
             if val = GetCurrentProcessID then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'GetCurrentProcessId'));
                found := true;
             end;
        end;

        if (to_trace[i]=$FF) and (to_trace[i+1]=$35) and (to_trace[i+6]=$58) then
        begin
             //check all the possible mov eax,[xxxxxx] redirections
             address := pointer((@to_trace[i+2])^);
             val     := address^;
             //val = eax returned by redirection code. try to id emulated function
             if val = GetVersion then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'GetVersion'));
                found := true;
             end;
             if val = dword(GetCommandLineA) then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'GetCommandLineA'));
                found := true;
             end;
             if val = GetCurrentProcess then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'GetCurrentProcess'));
                found := true;
             end;
             if val = GetCurrentProcessID then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'GetCurrentProcessId'));
                found := true;
             end;
        end;
        end;

        //check for ret 4 at certain position (lock/free resource)
        if (to_trace[4]=$C2) and (to_trace[5]=$04) then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'FreeResource'));
                found := true;
        end;

        //check for call and ret 4 at certain position (freeresource->getversion)
        if (to_trace[3]=$E8) and (to_trace[10]=$04) then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'FreeResource'));
                found := true;
        end;

        //check for lockresource
        if (to_trace[8]=$8B) and (to_trace[10]=$08) and (to_trace[11]=$5D) then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'LockResource'));
                found := true;
        end;

        //check for mov eax,[xxxxxx] and ret 4 at certain position (lockresource)
        if (to_trace[3]=$8B) and (to_trace[7]=$C2) then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'LockResource'));
                found := true;
        end;

        //check for GetProcAddress
        if (to_trace[5]=$C) and (to_trace[8]=$8) then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'GetProcAddress'));
                found := true;
        end;

        //check for GetModuleHandle
        if (to_trace[5]=$8) and (to_trace[15]=$EB) then begin
                val := dword(GetProcAddress(GetModuleHandle('KERNEL32.DLL'),'GetModuleHandleA'));
                found := true;
        end;

        //check for DialogBoxParamA
        if (to_trace[6]=$8) and (to_trace[9]=$18) then begin
                val := dword(GetProcAddress(GetModuleHandle('USER32.DLL'),'DialogBoxParamA'));
                found := true;
        end;

        if found then
        begin
                dwPtrOutput^ := val;
	        // OK
                Trace := 200;
	end
        else Trace := 300; //completed, but nothing found

        UnmapViewOfFile(pointer(dwPtrOutput));
        CloseHandle(hFileMap);

end;

exports Trace;

begin
        // Initialize all you need
end.
