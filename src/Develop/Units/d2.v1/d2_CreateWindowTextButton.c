extern int d2_CurrentWindowId;
extern char* d2_Controls;


int __cdecl d2_AddWindowTextButton(char*, int, int, int, int);
void __cdecl d2_SetElementFont(int, int);
void __cdecl d2_SetElementWidth(int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl d2_CreateWindowTextButton(char* a, int b, int c)
{
	int h;

	h = d2_AddWindowTextButton(a + 3, b, 0xc5, c, d2_CurrentWindowId);
	d2_SetElementFont(h, 0x54);
	((D2_CONTROL_TL*) (d2_Controls))[h].value_06c = 1;
	d2_SetElementWidth(h, 0x60);
	return h;
}
