#include <windows.h>

extern BOOL __stdcall fcn_0041adc0(HWND, UINT, WPARAM, LPARAM);

/* ADDRESS: GOLDTL 0x0041ad80 */
char __cdecl fcn_0041ad80(int unused, HWND owner)
{
	HINSTANCE library;

	if (*(unsigned *) 0x6b5de8 > 0) {
		library = LoadLibraryA((const char *) 0x6777e4);
		if (library != 0) {
			DialogBoxParamA(library, (const char *) 0x65, owner, fcn_0041adc0, 0);
			FreeLibrary(library);
			return 1;
		}
	}
	return 0;
}
