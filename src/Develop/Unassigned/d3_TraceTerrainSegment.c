


#include <math.h>
#include <stdlib.h>

// SIZE 0xc
typedef struct {
	float x;
	float y;
	float z;
} V3;

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} V4;

extern float g_6ad624;
extern float g_6628a0;

void __cdecl d3sm_SampleHeight(void*, V3*, int*, int*, float*);

int __cdecl d3_TraceTerrainSegment(void* map, V3* from, V3* to, int gx, int gy, int* ox, int* oy)
{
	int cx;
	V4 d;
	V4 cur;
	int cy;
	float h;
	float t;
	float step;
	int dx;
	int dy;

	d3sm_SampleHeight(map, to, ox, oy, &h);
	dx = abs(*ox - gx);
	dy = abs(*oy - gy);
	if (dx <= 1 && dy <= 1) {
		if (g_6ad624 + h > to->y) {
			return 1;
		}
		return 0;
	}
	step = g_6628a0 / (float) sqrt((float) (dy * dy) + dx * dx);
	d.x = to->x - from->x;
	d.y = to->y - from->y;
	d.z = to->z - from->z;
	cur.x = from->x;
	cur.y = from->y;
	cur.z = from->z;
	d.x *= step;
	d.y *= step;
	d.z *= step;
	t = 0.0f;
	do {
		cur.x = d.x + cur.x;
		cur.y = d.y + cur.y;
		cur.z = d.z + cur.z;
		d3sm_SampleHeight(map, (V3*) &cur, &cx, &cy, &h);
		if (g_6ad624 + h > cur.y) {
			to->x = cur.x;
			to->y = cur.y;
			to->z = cur.z;
			return 1;
		}
		t += step;
	} while (t < g_6628a0);
	return 0;
}
