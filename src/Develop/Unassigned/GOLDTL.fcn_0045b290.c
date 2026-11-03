#include <string.h>

extern char* g_6b8014;
extern int g_67a370;

typedef struct {
	float mn[3];
	int pad;
	float mx[3];
} Box_45b290;

void __cdecl fcn_004379a0(int, int, int, void*, void*);
void __cdecl fcn_0045a910(void);
void __cdecl fcn_0045a9d0(void);
void __cdecl fcn_0045a3a0(int*, int*);
void __cdecl fcn_0045b1d0(int*, int, int);

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0045b290 */
void __cdecl fcn_0045b290(int* m, unsigned char* t)
{
	Box_45b290 box;
	float pts[8][3];
	float* f;
	int* cells;
	unsigned char* bytes;
	unsigned char* p;
	int n;
	int i;
	int j;
	int minb;
	int maxb;
	float n0;
	float range;
	float x;
	float y;
	float z;
	float minx;
	float maxx;
	float miny;
	float maxy;
	float minz;
	float maxz;

	if (!m || m[8] < 1)
		return;
	if (*(int*) (m + 0x28) == 0)
		return;
	if (!g_6b8014)
		return;
	box.mn[0] = 1e10f;
	box.mn[1] = 1e10f;
	box.mn[2] = 1e10f;
	box.mx[0] = -1e10f;
	box.mx[1] = -1e10f;
	box.mx[2] = -1e10f;
	fcn_004379a0(g_67a370, 0, 0x40, fcn_0045a910, &box);
	n = m[8];
	cells = (int*) m[9];
	if (cells) {
		memset(cells, 0, n * n * 0x1c);
		for (i = 0; i < n * n; i++)
			cells[i * 7] = 1;
	}
	if (t) {
		f = (float*) t;
		minb = 0xff;
		maxb = 0;
		p = t + 0x28c;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				if (p[1] > maxb)
					maxb = p[1];
				if (p[0] < minb)
					minb = p[0];
				p += 500;
			}
		}
		n0 = (float) *(int*) t;
		pts[0][0] = (float) minb * f[0x20] + f[0x14];
		pts[0][1] = (float) minb * f[0x21] + f[0x15];
		pts[0][2] = (float) minb * f[0x22] + f[0x16];
		pts[1][0] = n0 * f[0x18] + pts[0][0];
		pts[1][1] = n0 * f[0x19] + pts[0][1];
		pts[1][2] = n0 * f[0x1a] + pts[0][2];
		pts[2][0] = n0 * f[0x1c] + pts[0][0];
		pts[2][1] = n0 * f[0x1d] + pts[0][1];
		pts[2][2] = n0 * f[0x1e] + pts[0][2];
		pts[3][0] = n0 * f[0x18] + pts[2][0];
		pts[3][1] = n0 * f[0x19] + pts[2][1];
		pts[3][2] = n0 * f[0x1a] + pts[2][2];
		range = (float) (maxb - minb);
		for (i = 0; i < 4; i++) {
			pts[4 + i][0] = pts[i][0] + range * f[0x20];
			pts[4 + i][1] = pts[i][1] + range * f[0x21];
			pts[4 + i][2] = pts[i][2] + range * f[0x22];
		}
		minx = 1e10f;
		miny = 1e10f;
		minz = 1e10f;
		maxx = -1e10f;
		maxy = -1e10f;
		maxz = -1e10f;
		for (i = 0; i < 8; i++) {
			x = pts[i][0];
			y = pts[i][1];
			z = pts[i][2];
			if (x <= minx)
				minx = x;
			if (y <= miny)
				miny = y;
			if (z <= minz)
				minz = z;
			if (maxx <= x)
				maxx = x;
			if (maxy <= y)
				maxy = y;
			if (maxz <= z)
				maxz = z;
		}
		if (miny <= box.mn[1])
			box.mn[1] = miny;
		if (box.mx[1] <= maxy)
			box.mx[1] = maxy;
		box.mn[0] = minx;
		box.mx[0] = maxx;
		box.mn[2] = minz;
		box.mx[2] = maxz;
	}
	m[2] = *(int*) &box.mx[2];
	*(float*) (m + 1) = box.mn[1] + 1.0f;
	*(float*) m = box.mn[0];
	*(float*) (m + 4) = (box.mx[0] - box.mn[0]) / ((float) n - 1.75f);
	*(float*) (m + 5) = (box.mx[1] - box.mn[1]) * 0.0039525693f;
	*(float*) (m + 6) = (box.mn[2] - box.mx[2]) / ((float) n - 1.75f);
	if (t) {
		fcn_0045a3a0((int*) t, m);
	} else {
		bytes = (unsigned char*) m[10];
		memset(bytes, 0, n * n);
	}
	fcn_004379a0(g_67a370, 0, 0x40, fcn_0045a9d0, m);
	if (m[9]) {
		fcn_0045b1d0(m, 0xb, 0xc);
		for (i = 0; i < n; i++) {
			cells[i * 7] = 0xd;
			cells[((n - 1) * n + i) * 7] = 0xd;
			cells[(n * i) * 7] = 0xd;
			cells[(n * (i + 1) - 1) * 7] = 0xd;
		}
	}
}
