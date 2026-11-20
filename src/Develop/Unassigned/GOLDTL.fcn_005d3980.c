


// SIZE 0x14
#include "client_types.h"
typedef GRAPH_SAMPLE Sample;

// SIZE 0x28
typedef struct {
	int id;
	float a;
	float b;
	float c;
	char pad10[0x18];
} GRAPH_VALUE;

extern GRAPH_SAMPLE g_99ec20[16];

void __cdecl fcn_00472c30(int, int, int, int, int, int, int);

#define CLAMP0(v) ((v) > 0.0 ? (v) : 0.0)

void __cdecl fcn_005d3980(GRAPH_VALUE cur, int w, int h)
{
	int step;
	float scale;
	float base;
	int x;
	int nx;
	int i;
	float previous;
	float sample;

	step = (w - 0x69) / 16;
	scale = (float) (h - 0x1e);
	base = (float) (h - 0x16);
	x = 0x2d;
	for (i = 1; i < 16; i++) {
		previous = (float)(CLAMP0(g_99ec20[i - 1].a));
		sample = (float)(CLAMP0(g_99ec20[i].a));
		nx = x + step;
		fcn_00472c30(x, (int) (base - previous * scale), nx, (int) (base - sample * scale), 0xee, 0xee, 0x10);
		x = nx;
	}
	previous = (float)(CLAMP0(g_99ec20[15].a));
	sample = (float)(CLAMP0(cur.a));
	fcn_00472c30(step * 15 + 0x2d, (int) (base - previous * scale), step * 16 + 0x2d, (int) (base - sample * scale), 0xee, 0xee, 0x10);
}
