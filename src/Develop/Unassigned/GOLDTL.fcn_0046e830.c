#include "Develop/Units/d2.v1/d2_win.h"




// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_0046e830_Ent;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
#include "Develop/Units/d2.v1/d2_gui.h"

int __cdecl d2_AddElementToWindow(int x, int y, int a3, int win);

/* ADDRESS: GOLDTL 0x0046e830 */
void __cdecl fcn_0046e830(int x, int y, int win, int target, int id)
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
	*(int*) &((D2_WIN*)g_1015f40)[target].pad3c[0x238] = 0x30;
}
