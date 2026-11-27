#include <windows.h>

extern BOOL __stdcall d3_DisplaySetupDlgProc(HWND, UINT, WPARAM, LPARAM);

/* ADDRESS: GOLDTL 0x0041ad80 */
char __cdecl d3_ShowDisplaySetupDialog(int unused, HWND owner)
{
	HINSTANCE library;

	if (*(unsigned *) 0x6b5de8 > 0) {
		library = LoadLibraryA((const char *) 0x6777e4);
		if (library != 0) {
			DialogBoxParamA(library, (const char *) 0x65, owner, d3_DisplaySetupDlgProc, 0);
			FreeLibrary(library);
			return 1;
		}
	}
	return 0;
}
