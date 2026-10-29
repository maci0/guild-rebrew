typedef struct
{
	int i[0x3cc / 4];
} fcn_0046f100_Win;
// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} fcn_0046f100_Ent;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;

int __cdecl fcn_0046e940(int x, int y, int w, int h, int a5);

/* ADDRESS: GOLDTL 0x0046f100 */
int __cdecl fcn_0046f100(int x, int y, int cx, int cy, int a5, int win)
{
	fcn_0046f100_Win* w;
	int id;

	w = &((fcn_0046f100_Win*)g_1015f40)[win];
	if (w->i[0x290 / 4] == 0) {
		return -1;
	}
	id = fcn_0046e940(w->i[0x4 / 4] - w->i[0x268 / 4] + x, w->i[0x8 / 4] - w->i[0x258 / 4] + y, cx, cy, a5);
	((int*) w->i[0x28 / 4])[w->i[0x2c / 4]] = ((fcn_0046f100_Win*)g_1015f40)[id].i[0x27c / 4];
	((fcn_0046f100_Ent*)g_1015ea0)[((fcn_0046f100_Win*)g_1015f40)[id].i[0x27c / 4]].i[0x40 / 4] = (int) w;
	((fcn_0046f100_Ent*)g_1015ea0)[((fcn_0046f100_Win*)g_1015f40)[id].i[0x27c / 4]].i[0x30 / 4] = w->i[0x8 / 4] + y;
	((fcn_0046f100_Ent*)g_1015ea0)[((fcn_0046f100_Win*)g_1015f40)[id].i[0x27c / 4]].i[0x34 / 4] = w->i[0x8 / 4] + y + cy;
	((fcn_0046f100_Ent*)g_1015ea0)[((fcn_0046f100_Win*)g_1015f40)[id].i[0x27c / 4]].i[0x28 / 4] = w->i[0x4 / 4] + x;
	((fcn_0046f100_Ent*)g_1015ea0)[((fcn_0046f100_Win*)g_1015f40)[id].i[0x27c / 4]].i[0x2c / 4] = w->i[0x4 / 4] + x + cx;
	((fcn_0046f100_Ent*)g_1015ea0)[((fcn_0046f100_Win*)g_1015f40)[id].i[0x27c / 4]].i[0x50 / 4] = ((fcn_0046f100_Ent*)g_1015ea0)[w->i[0x27c / 4]].i[0x50 / 4];
	w->i[0x2c / 4]++;
	if (y + ((fcn_0046f100_Win*)g_1015f40)[id].i[0x10 / 4] > w->i[0x254 / 4]) {
		w->i[0x254 / 4] = y + ((fcn_0046f100_Win*)g_1015f40)[id].i[0x10 / 4];
	}
	return id;
}
