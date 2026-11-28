extern char g_6b5de8[];
#include <windows.h>

extern BOOL __stdcall d3_DisplaySetupDlgProc(HWND, UINT, WPARAM, LPARAM);

/* ADDRESS: GOLDTL 0x0041ad80 */
/* ADDRESS: GOLDDE 0x00418ac0 */
char __cdecl d3_ShowDisplaySetupDialog(int unused, HWND owner)
{
	HINSTANCE library;

	if (*(unsigned *) &g_6b5de8 > 0) {
		library = LoadLibraryA("d8_resource.dll");
		if (library != 0) {
			DialogBoxParamA(library, (const char *) 0x65, owner, d3_DisplaySetupDlgProc, 0);
			FreeLibrary(library);
			return 1;
		}
	}
	return 0;
}
