

#include "client_types.h"
typedef Win_1015f40 Win;
// SIZE 0x3cc

typedef struct
{
	unsigned short* x0;
	char pad4[0xc];
	int x10;
	int x14;
	char pad18[0x14];
	int x2c;
	char pad30[8];
} Item;
// SIZE 0x38

extern int g_772514;
extern Win_1015f40 g_1015f40[0x60];
extern int g_14aad98;
extern int g_14aad9c[];
extern char s_6a9680[];

int __cdecl fcn_005cc240(int, int, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_005c9090(int, int, int, int, int);
void __cdecl fcn_005ca740(int, int, int, int, Item*, int);
void __cdecl fcn_005c9160(int, int, int, int, int);
void __cdecl fcn_005cc2f0(unsigned int, Item*);

int __cdecl fcn_005cc720(int a1, int a2, int a3, unsigned int n, Item* items)
{
	int y;
	char buf[0x100];
	int half;
	unsigned int i;

	if (n == 0) {
		return 0;
	}
	y = fcn_005cc240(a1, a2, a3);
	half = g_1015f40[g_772514].xc / 2;
	fcn_0051af00(buf, (int) s_6a9680, *items[0].x0);
	fcn_005c9090((int) buf, half, 8, half * 2, 0x55);
	fcn_005c9090(g_14aad98, half, 0x20, half * 2, 0x55);
	fcn_0051af00(buf, (int) s_6a9680, *items[1].x0);
	fcn_005c9090((int) buf, half, 0x38, half * 2, 0x55);
	for (i = 0; i < n; i++) {
		items[i].x10 = 0x4b;
		items[i].x14 = i * 0x70 + 0x52;
		fcn_005ca740(0x4b, i * 0x70 + 0x52, g_772514, 0x56, &items[i], 1);
		fcn_005c9160(g_14aad9c[items[i].x2c], 0x14a, i * 0x70 + 0x52 + 0x1e, 200, 0x55);
	}
	fcn_005cc2f0(n, items);
	g_1015f40[g_772514].x258 = y;
	g_1015f40[g_772514].x274 = 0x70;
	return 1;
}
