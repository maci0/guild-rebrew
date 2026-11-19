

#include "client_types.h"
#include "Develop/Units/d2.v1/d2_win.h"
// SIZE 0x3cc

typedef struct
{
	char pad0[0x10];
	int x10;
	int x14;
	char pad18[0x20];
} Item;
// SIZE 0x38

extern int d2_CurrentWindowId;
extern char* g_772500;
extern Win_1015f40 g_1015f40[0x60];
extern int g_14aad8c;

int __cdecl fcn_005cc240(int, int, int);
void __cdecl fcn_005c9090(int, int, int, int, int);
void __cdecl fcn_005ca740(int, int, int, int, Item*, int);
void __cdecl fcn_005cc2f0(unsigned int, Item*);

int __cdecl fcn_005cc420(int a1, int a2, int a3, unsigned int n, Item* items)
{
	int y;
	int half;
	unsigned int i;

	if (n == 0) {
		return 0;
	}
	y = fcn_005cc240(a1, a2, a3);
	half = ((D2_WIN*)g_1015f40)[d2_CurrentWindowId].width / 2;
	fcn_005c9090(g_14aad8c, half, 8, half * 2, 0x55);
	for (i = 0; i < n; i++) {
		items[i].x10 = (((D2_WIN*)g_1015f40)[d2_CurrentWindowId].width - *(short*) (g_772500 + 0x1ebd8)) / 2;
		items[i].x14 = i * 0x70 + 0x28;
		fcn_005ca740(items[i].x10, i * 0x70 + 0x28, d2_CurrentWindowId, 0x56, &items[i], 1);
	}
	fcn_005cc2f0(n, items);
	*(int*) &((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3c[0x21c] = y;
	*(int*) &((D2_WIN*)g_1015f40)[d2_CurrentWindowId].pad3c[0x238] = 0x70;
	return 1;
}
