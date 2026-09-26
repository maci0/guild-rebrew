// FUNCTION: GOLD 0x005c7800
// SIZE: 325
// FUNCTION: GOLDTL 0x005d3ad0
// SIZE: 325

// SIZE 0x14
#include "client_types.h"
typedef Sample_99ec20 Sample;

// SIZE 0x28
typedef struct {
	int id;
	float a;
	float b;
	float c;
	char pad10[0x18];
} Cur;

extern Sample_99ec20 g_99ec20[16];
extern double g_662950;

void __cdecl fcn_00472c30(int, int, int, int, int, int, int);

#define CLAMP0(v) ((v) > g_662950 ? (v) : g_662950)

void __cdecl fcn_005d3ad0(Cur cur, int w, int h)
{
	int step;
	float scale;
	float base;
	int x;
	int nx;
	int i;
	float v0;
	float v1;

	step = (w - 0x69) / 16;
	scale = (float) (h - 0x1e);
	base = (float) (h - 0x16);
	x = 0x2d;
	for (i = 1; i < 16; i++) {
		v0 = CLAMP0(g_99ec20[i - 1].c);
		v1 = CLAMP0(g_99ec20[i].c);
		nx = x + step;
		fcn_00472c30(x, (int) (base - v0 * scale), nx, (int) (base - v1 * scale), 0xee, 0x10, 0xee);
		x = nx;
	}
	v0 = CLAMP0(g_99ec20[15].c);
	v1 = CLAMP0(cur.c);
	fcn_00472c30(step * 15 + 0x2d, (int) (base - v0 * scale), step * 16 + 0x2d, (int) (base - v1 * scale), 0xee, 0x10, 0xee);
}
