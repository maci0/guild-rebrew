


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

void __cdecl d2_DrawLine(int, int, int, int, int, int, int);

#define CLAMP0(v) ((v) > 0.0 ? (v) : 0.0)

void __cdecl d2_DrawMagentaHistoryGraph(GRAPH_VALUE cur, int w, int h)
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
		d2_DrawLine(x, (int) (base - prevValue * scale), nx, (int) (base - nextValue * scale), 0xee, 0x10, 0xee);
		x = nx;
	}
	prevValue = (float)(CLAMP0(g_99ec20[15].c));
	nextValue = (float)(CLAMP0(cur.c));
	d2_DrawLine(step * 15 + 0x2d, (int) (base - prevValue * scale), step * 16 + 0x2d, (int) (base - nextValue * scale), 0xee, 0x10, 0xee);
}
