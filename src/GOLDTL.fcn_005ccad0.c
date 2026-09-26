// FUNCTION: GOLDTL 0x005ccad0
// SIZE: 272

#include "client_types.h"
typedef Win_1015f40 Win;
// SIZE 0x3cc

typedef struct
{
	char pad0[0x10];
	int x10;
	int x14;
	char pad18[0x1c];
	int x34;
} Item;
// SIZE 0x38

extern int g_772514;
extern Win_1015f40 g_1015f40[0x60];
extern int g_14aadc8;
extern int g_14a5c6c[];

int __cdecl fcn_005cc240(int, int, int);
void __cdecl fcn_005c9090(int, int, int, int, int);
void __cdecl fcn_005ca740(int, int, int, int, Item*, int);
void __cdecl fcn_005cc2f0(unsigned int, Item*);

int __cdecl fcn_005ccad0(int a1, int a2, int a3, unsigned int n, Item* items)
{
	int y;
	int half;
	int pos;
	int cat;
	unsigned int i;

	if (n == 0) {
		return 0;
	}
	y = fcn_005cc240(a1, a2, a3);
	half = g_1015f40[g_772514].xc / 2;
	fcn_005c9090(g_14aadc8, half, 8, half * 2, 0x55);
	pos = 0x28;
	cat = 0x28;
	for (i = 0; i < n; i++) {
		if (items[i].x34 != cat) {
			cat = items[i].x34;
			fcn_005c9090(g_14a5c6c[cat], half, pos, half * 2, 0x55);
			pos += 0x19;
		}
		items[i].x10 = 0x4b;
		items[i].x14 = pos;
		fcn_005ca740(0x4b, pos, g_772514, 0x56, &items[i], 1);
		pos += 0x70;
	}
	fcn_005cc2f0(n, items);
	g_1015f40[g_772514].x258 = y;
	g_1015f40[g_772514].x274 = 0x70;
	return 1;
}
