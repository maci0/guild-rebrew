#include "gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"
#include "Develop/Units/d2.v1/d2_win.h"
#include "client_types.h"
#include "Develop/Units/d2.v1/d2_gui.h"

// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} D2_SCROLL_BTN_ENT;
// SIZE 0x2f4

extern GOLD_GUI_WINDOW g_00f8f120[]; /* 0x00f8f120 */
extern GuiEnt* g_00f8f080; /* 0x00f8f080 */
extern Win_1015f40 g_1015f40[0x60];

int __cdecl d2_AddElementToWindow(int x, int y, int id, int win);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00472260 */
void __cdecl d2_AddWindowScrollButtons(int x, int y, int win, int target, int id)
{
	int wo;

	wo = win * sizeof(GOLD_GUI_WINDOW);
	if (x == -1 && y == -1) {
		x = *(short*) ((char*) g_00f8f120 + wo + 0x8) - 0x20;
		y = *(short*) ((char*) g_00f8f120 + wo + 0xa) - 0x20;
	}
	*(int*) ((char*) g_00f8f120 + wo + 0x3ac) = d2_AddElementToWindow(x, y, id, win);
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3ac)].target = target;
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3ac)].flags = 3;
	x -= 0x20;
	*(int*) ((char*) g_00f8f120 + wo + 0x3a8) = d2_AddElementToWindow(x, y, id + 1, win);
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3a8)].target = target;
	g_00f8f080[*(int*) ((char*) g_00f8f120 + wo + 0x3a8)].flags = 3;
	*(int*) ((char*) g_00f8f120 + wo + 0x248) = 0;
	g_00f8f120[target].step = 0x30;
}
#else
/* ADDRESS: GOLDTL 0x0046e830 */
void __cdecl d2_AddWindowScrollButtons(int x, int y, int win, int target, int id)
{
	int wo;
	short sy;

	wo = win * sizeof(D2_WIN);
	if (x == -1 && y == -1) {
		x = ((D2_WIN*)((char*)g_1015f40 + wo))->width - 0x20;
		y = ((D2_WIN*)((char*)g_1015f40 + wo))->height - 0x20;
	}
	sy = (short) y;
	*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3a8[0x14] = d2_AddElementToWindow((short) x, sy, id, win);
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3a8[0x14]].value_1f0) = target;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3a8[0x14]].flags_1d0) = 3;
	x -= 0x20;
	*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3a8[0x10] = d2_AddElementToWindow((short) x, sy, id + 1, win);
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3a8[0x10]].value_1f0) = target;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3a8[0x10]].flags_1d0) = 3;
	*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3c[0x21c] = 0;
	*(int*) &((D2_WIN*) g_1015f40)[target].pad3c[0x238] = 0x30;
}
#endif
