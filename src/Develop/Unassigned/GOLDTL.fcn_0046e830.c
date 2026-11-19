#include "Develop/Units/d2.v1/d2_win.h"




// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_0046e830_Ent;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;

int __cdecl fcn_0046f740(int x, int y, int a3, int win);

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
	*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3a8[0x14] = fcn_0046f740((short) x, sy, id, win);
	((fcn_0046e830_Ent*)g_1015ea0)[*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3a8[0x14]].i[0x1f0 / 4] = target;
	((fcn_0046e830_Ent*)g_1015ea0)[*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3a8[0x14]].i[0x1d0 / 4] = 3;
	x -= 0x20;
	*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3a8[0x10] = fcn_0046f740((short) x, sy, id + 1, win);
	((fcn_0046e830_Ent*)g_1015ea0)[*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3a8[0x10]].i[0x1f0 / 4] = target;
	((fcn_0046e830_Ent*)g_1015ea0)[*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3a8[0x10]].i[0x1d0 / 4] = 3;
	*(int*) &((D2_WIN*)((char*)g_1015f40 + wo))->pad3c[0x21c] = 0;
	*(int*) &((D2_WIN*)g_1015f40)[target].pad3c[0x238] = 0x30;
}
