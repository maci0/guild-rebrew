

extern int d2_CurrentWindowId;
extern int g_1015f78[];
extern int g_772544;
extern int g_772548;
extern int g_77254c;
extern int g_772550;
extern char* g_1015ea0;

void __cdecl d2_SelectFont(int);
void __cdecl fcn_0046bd20(int, int, int, int, int, int, int);
void __cdecl d2_ClearPaintboxRect(int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetElementFont(int, int);

void __cdecl fcn_005c9090(int text, int x, int y, int w, int font)
{
	int r;

	d2_SelectFont(font);
	if (g_1015f78[d2_CurrentWindowId * 243] != 0) {
		fcn_0046bd20(x - w / 2, y, w, 0x140, 0, text, 8);
		d2_ClearPaintboxRect(g_77254c, g_772550, g_772544, g_772548);
	}
	r = d2_ShowTxt(x - w / 2, y, (char*) text, d2_CurrentWindowId);
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[r].value_06c)) = 1;
	*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[r].width)) = w;
	d2_SetElementFont(r, font);
}
