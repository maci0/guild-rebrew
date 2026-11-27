

extern int d2_CurrentWindowId;
extern char* g_f8f080;

int __cdecl d2_AddElementToWindow(int, int, int, int);
float __cdecl gm_GetSeasonPrice(int, int);
void __cdecl d2_FormatCurrencyString(int, int, char*);
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl d2_AddTradeGoodPriceTile(int x, int y, int layer, int a4, int a5)
{
	char text[0x40];
	int r;
	int w;
	float f;

	d2_AddElementToWindow(x, y, 0x525, layer);
	r = d2_AddElementToWindow(x + 2, y + 2, a4 + 0xdf, layer);
	d2_AddElementToWindow(x + 3, y + 0x35, 0x746, layer);
	*(int*) (g_f8f080 + r * 748 + 0x4c) = 1;
	f = gm_GetSeasonPrice(a4, a5);
	d2_FormatCurrencyString((int) f, a5, text);
	w = d2_ShowTxt(x + 7, y + 0x3a, text, d2_CurrentWindowId);
	*(short*) (g_f8f080 + w * 748 + 0x14) = 0x24;
	*(short*) (g_f8f080 + w * 748 + 0x74) = 0x54;
	*(int*) (g_f8f080 + w * 748 + 0x60) = 1;
	return r;
}
