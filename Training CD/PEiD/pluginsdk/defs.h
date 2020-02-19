//#include <windows.h>
#ifdef _DLLMACRO
	#define DllExport extern "C" __declspec( dllexport )
#else
	#define DllExport extern "C" __declspec( dllexport )
#endif


DllExport DWORD DoMyJob(HWND hMainDlg, char *szFname, DWORD lpReserved, LPVOID lpParam);
DllExport LPSTR LoadDll();
