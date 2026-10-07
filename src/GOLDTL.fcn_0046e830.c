typedef struct
{
	int i[0x3cc / 4];
} fcn_0046e830_Win;
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

// FUNCTION: GOLDTL 0x46e830
void __cdecl fcn_0046e830(int x, int y, int win, int target, int id)
{
	int wo;
	short sy;

	wo = win * sizeof(fcn_0046e830_Win);
	if (x == -1 && y == -1) {
		x = *(int*) ((char*) g_1015f40 + wo + 0xc) - 0x20;
		y = *(int*) ((char*) g_1015f40 + wo + 0x10) - 0x20;
	}
	sy = (short) y;
	*(int*) ((char*) g_1015f40 + wo + 0x3bc) = fcn_0046f740((short) x, sy, id, win);
	((fcn_0046e830_Ent*)g_1015ea0)[*(int*) ((char*) g_1015f40 + wo + 0x3bc)].i[0x1f0 / 4] = target;
	((fcn_0046e830_Ent*)g_1015ea0)[*(int*) ((char*) g_1015f40 + wo + 0x3bc)].i[0x1d0 / 4] = 3;
	x -= 0x20;
	*(int*) ((char*) g_1015f40 + wo + 0x3b8) = fcn_0046f740((short) x, sy, id + 1, win);
	((fcn_0046e830_Ent*)g_1015ea0)[*(int*) ((char*) g_1015f40 + wo + 0x3b8)].i[0x1f0 / 4] = target;
	((fcn_0046e830_Ent*)g_1015ea0)[*(int*) ((char*) g_1015f40 + wo + 0x3b8)].i[0x1d0 / 4] = 3;
	*(int*) ((char*) g_1015f40 + wo + 0x258) = 0;
	((fcn_0046e830_Win*)g_1015f40)[target].i[0x274 / 4] = 0x30;
}
