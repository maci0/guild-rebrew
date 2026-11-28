


typedef struct {
	float v;
	float pad[4];
} MOOD_GRAPH_SAMPLE;
// SIZE 0x14

typedef struct {
	float f[10];
} MOOD_GRAPH_VALUES;
// SIZE 0x28

#include "Develop/client_types.h"
extern Pt5d36_99ec2c g_99ec2c[16];

extern float g_6640cc;

void __cdecl d2_DrawLine(int, int, int, int, int, int, int);

void __cdecl d2_DrawMoodHistoryGraph(MOOD_GRAPH_VALUES s, int w, int h)
{
	int step;
	int i;
	int x0;
	int x1;
	float m;
	float sy;
	float by;
	float t;
	float u;

	step = (w - 0x69) / 16;
	m = (-1.0f);
	for (i = 0; i < 16; i++) {
		if (m < ((MOOD_GRAPH_SAMPLE*)g_99ec2c)[i].v) {
			m = ((MOOD_GRAPH_SAMPLE*)g_99ec2c)[i].v;
		}
	}
	x0 = 0x2d;
	sy = (float) (h - 0x1e);
	by = (float) (h - 0x20) + g_6640cc;
	for (i = 0; i < 15; i++) {
		x1 = x0 + step;
		t = ((MOOD_GRAPH_SAMPLE*)g_99ec2c)[i].v;
		u = ((MOOD_GRAPH_SAMPLE*)g_99ec2c)[i + 1].v;
		d2_DrawLine(x0, (int) (by - t * sy), x1, (int) (by - u * sy), 0x10, 0xee, 0x10);
		x0 = x1;
	}
	d2_DrawLine(step * 15 + 0x2d, (int) (by - ((MOOD_GRAPH_SAMPLE*)g_99ec2c)[15].v * sy), step * 16 + 0x2d, (int) (by - s.f[9] * sy), 0x10, 0xee, 0x10);
}
