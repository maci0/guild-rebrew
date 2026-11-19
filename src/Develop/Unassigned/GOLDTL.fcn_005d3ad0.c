


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

void __cdecl fcn_00472c30(int, int, int, int, int, int, int);

#define CLAMP0(v) ((v) > 0.0 ? (v) : 0.0)

void __cdecl fcn_005d3ad0(Cur cur, int w, int h)
{
	int step;
	float scale;
	float base;
	int x;
	int nx;
	int i;
	float prevValue;
	float nextValue;

	step = (w - 0x69) / 16;
	scale = (float) (h - 0x1e);
	base = (float) (h - 0x16);
	x = 0x2d;
	for (i = 1; i < 16; i++) {
		prevValue = (float)(CLAMP0(g_99ec20[i - 1].c));
		nextValue = (float)(CLAMP0(g_99ec20[i].c));
		nx = x + step;
		fcn_00472c30(x, (int) (base - prevValue * scale), nx, (int) (base - nextValue * scale), 0xee, 0x10, 0xee);
		x = nx;
	}
	prevValue = (float)(CLAMP0(g_99ec20[15].c));
	nextValue = (float)(CLAMP0(cur.c));
	fcn_00472c30(step * 15 + 0x2d, (int) (base - prevValue * scale), step * 16 + 0x2d, (int) (base - nextValue * scale), 0xee, 0x10, 0xee);
}
