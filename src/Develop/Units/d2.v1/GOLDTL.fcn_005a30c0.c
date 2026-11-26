

extern int d2_CurrentWindowId;
extern char* g_1015ea0;

int __cdecl d2_AddElementToWindow(int, int, int, int);
float __cdecl fcn_0050bb50(int id, unsigned char a);
void __cdecl fcn_0050bc10(int, int, char*);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl fcn_005a30c0(int x, int y, int layer, int itemId, int a5)
{
	char text[0x40];
	int r;
	int w;
	float f;

	d2_AddElementToWindow(x, y, 0x525, layer);
	r = d2_AddElementToWindow(x + 2, y + 2, itemId + 0xdf, layer);
	d2_AddElementToWindow(x + 3, y + 0x35, 0x746, layer);
	((D2_CONTROL_TL*) (g_1015ea0))[r].value_05c = 1;
	f = fcn_0050bb50(itemId, a5);
	fcn_0050bc10((int) f, a5, text);
	w = d2_ShowTxt(x + 7, y + 0x3a, text, d2_CurrentWindowId);
	((D2_CONTROL_TL*) (g_1015ea0))[w].width = 0x24;
	((D2_CONTROL_TL*) (g_1015ea0))[w].font = 0x54;
	((D2_CONTROL_TL*) (g_1015ea0))[w].value_070 = 1;
	return r;
}
