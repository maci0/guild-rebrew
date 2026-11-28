


// SIZE 0x14
#include "Develop/client_types.h"
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

/* ADDRESS: GOLDDE 0x005b51e0 */
void __cdecl d2_DrawYellowHistoryGraph(GRAPH_VALUE cur, int w, int h)
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
		d2_DrawLine(x, (int) (base - previous * scale), nx, (int) (base - sample * scale), 0xee, 0xee, 0x10);
		x = nx;
	}
	previous = (float)(CLAMP0(g_99ec20[15].a));
	sample = (float)(CLAMP0(cur.a));
	d2_DrawLine(step * 15 + 0x2d, (int) (base - previous * scale), step * 16 + 0x2d, (int) (base - sample * scale), 0xee, 0xee, 0x10);
}
