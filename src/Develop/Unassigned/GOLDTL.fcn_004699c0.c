extern int g_772504,d2_ClipLeft,d2_ClipRight,g_7725fc,d2_ClipBottom,d2_DefaultFont,d2_ResourceOffset;
typedef struct { char b[0x2f4]; } Slot;
int __cdecl fcn_00469890(void);
int __cdecl fcn_00466260(int, int*, int*);
void __cdecl d2_AddRefcount(int);
int __cdecl fcn_0047a200(int, int, int, int);
int __cdecl fcn_0047b620(int, int);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x004699c0 */
int __cdecl fcn_004699c0(unsigned int x, int y, int resourceId)
{
	int v4;
	int n;
	int idx;

	char* slot;
	char* tp;
	int kind;
	int r;

	v4 = 0;
	if (resourceId > g_772504) {
		return -1;
	}
	idx = fcn_00469890();

	slot = (char*) ((char*) ((Slot*) g_1015ea0 + idx));
	if (idx >= 0x400) {
		return -1;
	}
	fcn_00466260(resourceId, &v4, &n);
	*(int*) (slot + 0xc) = v4;
	*(int*) (slot + 8) = n;
	*(int*) (slot + 0x20) = *(int*) (*(int*) &g_772500 + 0x3c + n * 0x54);
	*(int*) (slot + 0x10) = x;
	*(int*) (slot + 0x14) = y;
	*(int*) (slot + 0x28) = d2_ClipLeft;
	*(int*) (slot + 0x2c) = d2_ClipRight;
	*(int*) (slot + 0x30) = g_7725fc;
	*(int*) (slot + 0x34) = d2_ClipBottom;
	*(int*) (slot + 0x24) = 2;
	*(int*) (slot + 0x84) = d2_DefaultFont;
	d2_AddRefcount(n);
	kind = *(int*) (slot + 0x20);
	if (kind == 8) {
		*(int*) (slot + 0x5c) = 1;
	}
	*(int*) (slot + 0x1e4) = -1;
	*(int*) (slot + 0x1e8) = 0;
	*(int*) (slot + 0x1ec) = 0;
	switch (kind) {
	case 1:
		tp = (char*) *(int*) ((char*) ((Slot*) g_1015ea0 + idx) + 0xc);
		*(int*) (slot + 0x18) = *(unsigned short*) (tp + 6);
		*(int*) (slot + 0x1c) = *(unsigned short*) (tp + 8);
		return idx;
	case 4:
		*(int*) ((char*) ((Slot*) g_1015ea0 + idx) + 0x88) = fcn_0047a200(x, y, *(int*) ((char*) ((Slot*) g_1015ea0 + idx) + 0xc), 0);
		tp = (char*) *(int*) ((char*) ((Slot*) g_1015ea0 + idx) + 0xc);
		*(int*) ((char*) ((Slot*) g_1015ea0 + idx) + 0x18) = *(unsigned short*) (tp + 6);
		*(int*) ((char*) ((Slot*) g_1015ea0 + idx) + 0x1c) = *(unsigned short*) (tp + 8);
		return idx;
	case 17:
		tp = (char*) *(int*) ((char*) ((Slot*) g_1015ea0 + idx) + 0xc);
		*(int*) ((char*) ((Slot*) g_1015ea0 + idx) + 0x18) = *(short*) (tp + 0xc);
		*(int*) ((char*) ((Slot*) g_1015ea0 + idx) + 0x1c) = *(short*) (tp + 0xe);
		*(int*) ((char*) ((Slot*) g_1015ea0 + idx) + 0x88) = 2;
		return idx;
	case 5:
	case 8:
		*(int*) (slot + 0x88) = d2_ResourceOffset;
		tp = (char*) *(int*) ((char*) ((Slot*) g_1015ea0 + idx) + 0xc);
		r = fcn_0047b620((int) tp, *(int*) ((char*) ((Slot*) g_1015ea0 + idx) + 0x88));
		*(int*) (slot + 0x18) = *(unsigned short*) (r + 2);
		*(int*) (slot + 0x1c) = *(unsigned short*) (r + 6);
		*(int*) (slot + 0x1dc) = -1;
		*(int*) (slot + 0x1e0) = -1;
		*(int*) (slot + 0x1d4) = *(unsigned short*) (tp + 6);
		*(int*) (slot + 0x1d8) = *(unsigned short*) (tp + 8);
		*(char*) ((char*) ((Slot*) g_1015ea0 + idx) + 0x7c) = 8;
		*(char*) ((char*) ((Slot*) g_1015ea0 + idx) + 0x7d) = 8;
		return idx;
	}
	return idx;
}
