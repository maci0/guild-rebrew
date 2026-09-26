// FUNCTION: GOLD 0x005c07a0
// SIZE: 312

typedef struct
{
	char pad0[8];
	short x8;
	char pada[0x248 - 0xa];
	int x248;
	char pad24c[0x18];
	int x264;
	char pad268[0x3c4 - 0x268];
} Win;
// SIZE 0x3c4

typedef struct
{
	char pad0[0x10];
	int x10;
	int x14;
	char pad18[0x14];
	int x2c;
	char pad30[4];
	int x34;
} Item;
// SIZE 0x38

extern int g_772514;
#include "client_types.h"
extern Win_f8f120 g_f8f120[];
extern int g_14aadc0[];

int __cdecl fcn_005cc240(int, int, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_005c9090(int, int, int, int, int);
void __cdecl fcn_005ca740(int, int, int, int, Item*, int);
void __cdecl fcn_005c9160(int, int, int, int, int);
void __cdecl fcn_005cc2f0(unsigned int, Item*);

int __cdecl fcn_005c07a0(int a1, int a2, int a3, unsigned int n, Item* items)
{
	int y;
	char buf[0x200];
	int half;
	unsigned int i;

	if (n == 0) {
		return 0;
	}
	y = fcn_005cc240(a1, a2, a3);
	half = ((Win*)g_f8f120)[g_772514].x8 / 2;
	fcn_0051af00(buf, 0x16a7, items[0].x34 + 0x253);
	fcn_005c9090((int) buf, half, 8, half * 2, 0x55);
	for (i = 0; i < n; i++) {
		items[i].x10 = 0x4b;
		items[i].x14 = i * 0x70 + 0x28;
		fcn_005ca740(0x4b, i * 0x70 + 0x28, g_772514, 0x56, &items[i], 1);
		fcn_005c9160(g_14aadc0[items[i].x2c], 0x14a, i * 0x70 + 0x28 + 0x1e, 200, 0x55);
	}
	fcn_005cc2f0(n, items);
	((Win*)g_f8f120)[g_772514].x248 = y;
	((Win*)g_f8f120)[g_772514].x264 = 0x70;
	return 1;
}
