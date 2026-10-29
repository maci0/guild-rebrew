#include <math.h>

extern int g_67a370;

void __cdecl fcn_00455350(char*, char*, float*);
char __cdecl fcn_0045b990(char*, float*, int*, int*, float*);
int __cdecl fcn_004ceba0(int, int);
void __cdecl fcn_0045b920(char*, int, int, float*);

/* ADDRESS: GOLDTL 0x004cecf0 */
unsigned int __cdecl fcn_004cecf0(char* a0, int* a1, int* a2, int a3)
{
	char* m;
	float start[3];
	float hit[3];
	float d;
	float dx;
	float dy;
	float dz;
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
	int size;
	int span;

	m = *(char**) ((char*) g_67a370 + 0xb0);
	size = *(int*) (m + 0x20);
	best1 = 1e8f;
	best2 = 0.0f;
	x1 = 0;
	y1 = 0;
	x2 = 0;
	y2 = 0;
	found = 0;
	fcn_00455350(a0, a0 + 0x4c, start);
	if (!fcn_0045b990(m, start, &col, &row, &height)) {
		return 0;
	}
	for (i = 0; i < 0x40; i++) {
		maxy = size - 1;
		if (row + i <= maxy) {
			maxy = row + i;
		}
		miny = (row - i < 0) ? 0 : row - i;
		for (y = miny; y <= maxy; y++) {
			span = i - ((row - y < 0) ? y - row : row - y);
			maxx = size - 1;
			if (span + col <= maxx) {
				maxx = span + col;
			}
			minx = (col - span < 0) ? 0 : col - span;
			for (x = minx; x <= maxx; x++) {
				if (!fcn_004ceba0(x, y)) {
					continue;
				}
				fcn_0045b920(m, x, y, hit);
				dx = hit[0] - start[0];
				dy = hit[1] - start[1];
				dz = hit[2] - start[2];
				d = (float) sqrt(dx * dx + dy * dy + dz * dz);
				if (d < best1 && d > 30.0) {
					found = 1;
					best1 = d;
					x1 = x;
					y1 = y;
				}
				if (d > best2 && d > 30.0) {
					found = 1;
					best2 = d;
					x2 = x;
					y2 = y;
				}
			}
		}
	}
	if (!found) {
		return 0;
	}
	if (a3 == 0) {
		*a1 = x1;
		*a2 = y1;
		return 1;
	}
	*a1 = x2;
	*a2 = y2;
	return 1;
}
