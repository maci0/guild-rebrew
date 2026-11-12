/* Mip-map preparation for one terrain image: writes the diagonal-split and
 * edge bits of level 0 and the two reduced levels, then the per-tile min/max
 * heights, and lets the texture code rebuild the surfaces. */

#include <stdlib.h>

char __cdecl fcn_0043c140(int*, int, int, int);
void __cdecl PrepareFloorWater(char*);
typedef struct Tile Tile;
void __cdecl fcn_0043c640(Tile*);
void __cdecl fcn_0043b990(char*);

/* ADDRESS: GOLDTL 0x0043c2c0 */
void __cdecl fcn_0043c2c0(int* a0)
{
	unsigned char div[3];
	int mask;
	int w;
	int n;
	int s;
	int lv;
	int x;
	int y;
	int x1;
	int y1;
	int i;
	int j;
	int tx;
	int ty;
	int row;
	unsigned char* h;
	unsigned char mn;
	unsigned char mx;
	unsigned char c;
	unsigned char* rec;

	mask = a0[3];
	div[0] = 1;
	div[1] = 2;
	div[2] = 4;
	w = a0[0];
	for (y = 0; y < w; y++) {
		y1 = (y + 1) & mask;
		for (x = 0; x < w; x++) {
			h = (unsigned char*) a0[4];
			x1 = (x + 1) & mask;
			((unsigned char*) a0[9])[y * w + x] =
			    ((abs(h[y * w + x] - h[y1 * w + x1]) <= abs(h[y * w + x1] - h[y1 * w + x])) * 2
			     | fcn_0043c140(a0, x, y, 1)) << 6;
		}
	}
	for (lv = 1; lv < 3; lv++) {
		s = div[lv];
		n = a0[0] / s;
		for (y = 0; y < n; y++) {
			y1 = (y * s + s) & mask;
			for (x = 0; x < n; x++) {
				x1 = (x * s + s) & mask;
				h = (unsigned char*) a0[4];
				((unsigned char*) a0[10 + lv - 1])[y * n + x] =
				    ((abs(h[(a0[0] * y + x) * s] - h[y1 * a0[0] + x1])
				      <= abs(h[a0[0] * s * y + x1] - h[y1 * a0[0] + x * s])) * 2
				     | fcn_0043c140(a0, x * s, y * s, s)) << 6;
			}
		}
	}
	PrepareFloorWater((char*) a0);
	rec = (unsigned char*) a0 + 0x28c;
	for (ty = 0; ty < 8; ty++) {
		for (tx = 0; tx < 8; tx++) {
			mn = 0xff;
			mx = 0;
			for (j = 0; j <= a0[1]; j++) {
				row = ((a0[1] * ty + j) & mask) * a0[0];
				for (i = 0; i <= a0[1]; i++) {
					c = ((unsigned char*) a0[4])[((a0[1] * tx + i) & mask) + row];
					if (mx <= c)
						mx = c;
					if (mn >= c)
						mn = c;
					if (a0[6] != 0) {
						c = ((unsigned char*) a0[6])[((a0[1] * tx + i) & mask) + row];
						if (c > 0) {
							if (mx <= c)
								mx = c;
							if (mn >= c)
								mn = c;
						}
					}
				}
			}
			rec[1] = mx;
			rec[0] = mn;
			rec[3] = 0xff;
			rec += 0x1f4;
		}
	}
	*(float*) ((char*) a0 + 0x802c) = 0.05f;
	*(float*) ((char*) a0 + 0x8030) = 0.25f;
	fcn_0043c640((Tile*) a0);
	fcn_0043b990((char*) a0);
	*(unsigned char*) ((char*) a0 + 0x8036) |= 1;
}
