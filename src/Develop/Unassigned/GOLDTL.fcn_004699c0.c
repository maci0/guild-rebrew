extern int g_772504,g_7725f8,g_67d964,g_7725fc,g_67d968,g_67d398,g_772568;
int __cdecl fcn_00469890(void);
int __cdecl fcn_00466260(int, int*, int*);
void __cdecl d2_AddRefcount(int);
int __cdecl fcn_0047a200(int, int, int, int);
int __cdecl fcn_0047b620(int, int);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x004699c0 */
int __cdecl fcn_004699c0(unsigned int a0, int a1, int a2)
{
	int v4;
	int n;
	int idx;
	int off;
	char* v1;
	char* tp;
	int kind;
	int r;

	v4 = 0;
	if (a2 > g_772504) {
		return -1;
	}
	idx = fcn_00469890();
	off = idx * 0x2f4;
	v1 = (char*) (off + *(int*) &g_1015ea0);
	if (idx >= 0x400) {
		return -1;
	}
	fcn_00466260(a2, &v4, &n);
	*(int*) (v1 + 0xc) = v4;
	*(int*) (v1 + 8) = n;
	*(int*) (v1 + 0x20) = *(int*) (*(int*) &g_772500 + 0x3c + n * 0x54);
	*(int*) (v1 + 0x10) = a0;
	*(int*) (v1 + 0x14) = a1;
	*(int*) (v1 + 0x28) = g_7725f8;
	*(int*) (v1 + 0x2c) = g_67d964;
	*(int*) (v1 + 0x30) = g_7725fc;
	*(int*) (v1 + 0x34) = g_67d968;
	*(int*) (v1 + 0x24) = 2;
	*(int*) (v1 + 0x84) = g_67d398;
	d2_AddRefcount(n);
	kind = *(int*) (v1 + 0x20);
	if (kind == 8) {
		*(int*) (v1 + 0x5c) = 1;
	}
	*(int*) (v1 + 0x1e4) = -1;
	*(int*) (v1 + 0x1e8) = 0;
	*(int*) (v1 + 0x1ec) = 0;
	switch (kind) {
	case 1:
		tp = (char*) *(int*) (off + *(int*) &g_1015ea0 + 0xc);
		*(int*) (v1 + 0x18) = *(unsigned short*) (tp + 6);
		*(int*) (v1 + 0x1c) = *(unsigned short*) (tp + 8);
		return idx;
	case 4:
		*(int*) (off + *(int*) &g_1015ea0 + 0x88) = fcn_0047a200(a0, a1, *(int*) (off + *(int*) &g_1015ea0 + 0xc), 0);
		tp = (char*) *(int*) (off + *(int*) &g_1015ea0 + 0xc);
		*(int*) (off + *(int*) &g_1015ea0 + 0x18) = *(unsigned short*) (tp + 6);
		*(int*) (off + *(int*) &g_1015ea0 + 0x1c) = *(unsigned short*) (tp + 8);
		return idx;
	case 5:
	case 8:
		*(int*) (v1 + 0x88) = g_772568;
		tp = (char*) *(int*) (off + *(int*) &g_1015ea0 + 0xc);
		r = fcn_0047b620((int) tp, *(int*) (off + *(int*) &g_1015ea0 + 0x88));
		*(int*) (v1 + 0x18) = *(unsigned short*) (r + 2);
		*(int*) (v1 + 0x1c) = *(unsigned short*) (r + 6);
		*(int*) (v1 + 0x1dc) = -1;
		*(int*) (v1 + 0x1e0) = -1;
		*(int*) (v1 + 0x1d4) = *(unsigned short*) (tp + 6);
		*(int*) (v1 + 0x1d8) = *(unsigned short*) (tp + 8);
		*(char*) (off + *(int*) &g_1015ea0 + 0x7c) = 8;
		*(char*) (off + *(int*) &g_1015ea0 + 0x7d) = 8;
		return idx;
	case 17:
		tp = (char*) *(int*) (off + *(int*) &g_1015ea0 + 0xc);
		*(int*) (off + *(int*) &g_1015ea0 + 0x18) = *(short*) (tp + 0xc);
		*(int*) (off + *(int*) &g_1015ea0 + 0x1c) = *(short*) (tp + 0xe);
		*(int*) (off + *(int*) &g_1015ea0 + 0x88) = 2;
		return idx;
	}
	return idx;
}
