#include "Develop/Units/d2.v1/d2_win.h"
// SIZE 0x3cc

typedef struct Slot {
	char pad0[0x20];
	int type;
	char pad24[0x2f4 - 0x24];
} Slot;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;

void __cdecl fcn_0046b2b0(int slot);

/* ADDRESS: GOLDTL 0x0046f2c0 */
int __cdecl d2_ClearWindowChildren(int win, int keep)
{
	int i;

	if (win > 0x60) {
		return 0;
	}
	if (!((D2_WIN*)g_1015f40)[win].active) {
		return 0;
	}
	for (i = ((D2_WIN*)g_1015f40)[win].count - 1; i >= 0; i--) {
		if (((D2_WIN*)g_1015f40)[win].children[i] == ((int*)((D2_WIN*)g_1015f40)[win].pad3a8)[4 + 0]) {
			((int*)((D2_WIN*)g_1015f40)[win].pad3a8)[4 + 0] = -1;
		} else if (((D2_WIN*)g_1015f40)[win].children[i] == ((int*)((D2_WIN*)g_1015f40)[win].pad3a8)[4 + 1]) {
			((int*)((D2_WIN*)g_1015f40)[win].pad3a8)[4 + 1] = -1;
		} else if (((D2_WIN*)g_1015f40)[win].children[i] == ((int*)((D2_WIN*)g_1015f40)[win].pad3a8)[4 + 2]) {
			((int*)((D2_WIN*)g_1015f40)[win].pad3a8)[4 + 2] = -1;
		}
		if (((Slot*)g_1015ea0)[((D2_WIN*)g_1015f40)[win].children[i]].type != 0x40 || keep) {
			fcn_0046b2b0(((D2_WIN*)g_1015f40)[win].children[i]);
		}
	}
	if ((*(char**) &((D2_WIN*)g_1015f40)[win].pad3c[0])) {
		(*(char**) &((D2_WIN*)g_1015f40)[win].pad3c[0])[0] = 0;
	}
	*(int*) &((D2_WIN*)g_1015f40)[win].pad3c[0x220] = -1;
	*(int*) &((D2_WIN*)g_1015f40)[win].pad3c[0x21c] = 0;
	*(int*) &((D2_WIN*)g_1015f40)[win].pad3c[0x218] = 0;
	return 1;
}
