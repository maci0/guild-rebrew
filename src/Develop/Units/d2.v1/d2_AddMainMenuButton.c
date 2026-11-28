extern char* d2_Controls;


int __cdecl d2_AddWindowTextButton(int, int, int, int, int);
void __cdecl d2_SetElementWidth(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_AddMainMenuButton(int a1, int a2, int a3)
{
	int id;

	id = d2_AddWindowTextButton(0x20, a1 * 0x2b + 0xa, 0xbf, a2, a3);
	((D2_CONTROL_TL*) ((char*) d2_Controls))[id].value_06c = 1;
	d2_SetElementWidth(id, 0x12c);
	return id;
}
