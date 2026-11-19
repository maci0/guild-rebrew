#include <math.h>
#include <stdlib.h>

extern int g_67a370;

void __cdecl d3_TransformPoint(char*, char*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
int __cdecl fcn_004ceba0(int, int);
void __cdecl d3_GridPointToWorld(char*, int, int, float*);

/* ADDRESS: GOLDTL 0x004cecf0 */
unsigned int __cdecl fcn_004cecf0(char* originNode, int* outColumn, int* outRow, int selectFarthest)
{
	char* m;
	float start[4];
	float hit[4];
	float d;
	float best1;
	float best2;
	int col;
	int row;
	float height;
	int x1;
	int y1;
	int x2;
	int y2;
	int found;
	int i;
	int x;
	int y;
	int maxx;
	int maxy;
	int minx;
	int miny;
	int span;

	m = *(char**) ((char*) g_67a370 + 0xb0);
	best1 = 1e8f;
	best2 = 0.0f;
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
	found = 0;
	i = 0;
	d3_TransformPoint(originNode, originNode + 0x4c, start);
	if (!fcn_0045b990(m, start, &col, &row, &height)) {
		return 0;
	}
	do {
		maxy = *(int*) (m + 0x20) - 1;
		if (maxy >= row + i) {
			maxy = row + i;
		}
		miny = row - i;
		if (miny < 0) miny = 0;
		for (y = miny; y <= maxy; y++) {
			span = i - abs(row - y);
			maxx = *(int*) (m + 0x20) - 1;
			if (maxx >= span + col) {
				maxx = span + col;
			}
			minx = col - span;
			if (minx < 0) minx = 0;
			for (x = minx; x <= maxx; x++) {
				if (!fcn_004ceba0(x, y)) {
					continue;
				}
				d3_GridPointToWorld(m, x, y, hit);
				hit[0] = start[0] - hit[0];
				hit[1] = start[1] - hit[1];
				hit[2] = start[2] - hit[2];
				d = sqrt(hit[2] * hit[2] + hit[1] * hit[1] + hit[0] * hit[0]);
				if (d < best1 && d > 30.0) {
					best1 = d;
					x1 = x;
					y1 = y;
					found = 1;
				}
				if (d > best2 && d > 30.0) {
					best2 = d;
					x2 = x;
					y2 = y;
					found = 1;
				}
			}
		}
		i++;
	} while (i < 0x40);
	if (!found) {
		return 0;
	}
	if (selectFarthest == 0) {
		*outColumn = x1;
		*outRow = y1;
		return 1;
	}
	*outColumn = x2;
	*outRow = y2;
	return 1;
}
