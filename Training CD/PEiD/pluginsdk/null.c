#include <windows.h>
#include "defs.h"

DWORD DoMyJob(HWND hMainDlg, char *szFname, DWORD lpReserved, LPVOID lpParam)
{
	//hMainDlg: HWND of PEiD window
	//szFname: Filename
	//lpReserved: PEiD passes 'PEiD' as the value
	//lpParam: NULL passed, for future use
 
	// Write your main code here

	return 1;
}

LPSTR LoadDll()
{
	return "Name of the plugin";
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		break;

		case DLL_THREAD_ATTACH:
		break;

		case DLL_THREAD_DETACH:
		break;
		
		case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


