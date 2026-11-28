

extern int d2_CurrentWindowId;
extern int g_1015f78[];
extern int g_772544;
extern int g_772548;
extern int g_77254c;
extern int g_772550;
extern char* d2_Controls;

void __cdecl d2_SelectFont(int);
void __cdecl d2_DrawWordWrappedText(int, int, int, int, int, int, int);
void __cdecl d2_ClearPaintboxRect(int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetElementFont(int, int);

/* ADDRESS: GOLDDE 0x005aaef0 */
void __cdecl d2_ShowCenteredText(int text, int x, int y, int w, int font)
{
	int r;

	d2_SelectFont(font);
	if (g_1015f78[d2_CurrentWindowId * 243] != 0) {
		d2_DrawWordWrappedText(x - w / 2, y, w, 0x140, 0, text, 8);
		d2_ClearPaintboxRect(g_77254c, g_772550, g_772544, g_772548);
	}
	r = d2_ShowTxt(x - w / 2, y, (char*) text, d2_CurrentWindowId);
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[r].value_06c)) = 1;
	*(int*) (((char*)&((D2_CONTROL_TL*)d2_Controls)[r].width)) = w;
	d2_SetElementFont(r, font);
}
