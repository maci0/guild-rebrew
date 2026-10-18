#include "client_d3_dialog.h"

/* ADDRESS: GOLD 0x0041cf60 */
void __cdecl fcn_0041cf60(int a, int unused, HWND owner, char flag, int context)
{
	HINSTANCE library;

	library = LoadLibraryA("d3_resource.dll");
	DialogArgument4 = flag;
	DialogArgument5 = context;
	DialogArgument1 = a;
	if (library != 0) {
		DialogBoxParamA(library, MAKEINTRESOURCEA(101), owner, fcn_0041c830, 0);
		FreeLibrary(library);
	}
}
