/* Mip-map preparation for one terrain image: writes the diagonal-split and
 * edge bits of level 0 and the two reduced levels, then the per-tile min/max
 * heights, and lets the texture code rebuild the surfaces. */

#include <stdlib.h>

char __cdecl d3_IsFloorBlockUniform(int*, int, int, int);
void __cdecl PrepareFloorWater(char*);
typedef struct Tile Tile;
void __cdecl d3_BuildTerrainTileMeshes(Tile*);
void __cdecl d3_RebuildFloorMeshes(char*);

/* ADDRESS: GOLDTL 0x0043c2c0 */
/* ADDRESS: GOLDDE 0x00434e90 */
void __cdecl d3_BuildFloorGeometry(int* floor)
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

	mask = floor[3];
	div[0] = 1;
	div[1] = 2;
	div[2] = 4;
	w = floor[0];
	for (y = 0; y < w; y++) {
		y1 = (y + 1) & mask;
		for (x = 0; x < w; x++) {
			h = (unsigned char*) floor[4];
			x1 = (x + 1) & mask;
			((unsigned char*) floor[9])[y * w + x] =
			    ((abs(h[y * w + x] - h[y1 * w + x1]) <= abs(h[y * w + x1] - h[y1 * w + x])) * 2
			     | d3_IsFloorBlockUniform(floor, x, y, 1)) * 0x40;
		}
	}
	for (lv = 1; lv < 3; lv++) {
		s = div[lv];
		n = floor[0] / s;
		for (y = 0; y < n; y++) {
			y1 = (y * s + s) & mask;
			for (x = 0; x < n; x++) {
				x1 = (x * s + s) & mask;
				h = (unsigned char*) floor[4];
				((unsigned char*) floor[10 + lv - 1])[y * n + x] =
				    ((abs(h[(floor[0] * y + x) * s] - h[y1 * floor[0] + x1])
				      <= abs(h[floor[0] * s * y + x1] - h[y1 * floor[0] + x * s])) * 2
				     | d3_IsFloorBlockUniform(floor, x * s, y * s, s)) * 0x40;
			}
		}
	}
	PrepareFloorWater((char*) floor);
	rec = (unsigned char*) floor + 0x28c;
	for (ty = 0; ty < 8; ty++) {
		for (tx = 0; tx < 8; tx++) {
			mn = 0xff;
			mx = 0;
			for (j = 0; j <= floor[1]; j++) {
				row = ((floor[1] * ty + j) & mask) * floor[0];
				for (i = 0; i <= floor[1]; i++) {
					c = ((unsigned char*) floor[4])[((floor[1] * tx + i) & mask) + row];
					if (mx <= c)
						mx = c;
					if (mn >= c)
						mn = c;
					if (floor[6] != 0) {
						c = ((unsigned char*) floor[6])[((floor[1] * tx + i) & mask) + row];
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
	*(float*) ((char*) floor + 0x802c) = 0.05f;
	*(float*) ((char*) floor + 0x8030) = 0.25f;
	d3_BuildTerrainTileMeshes((Tile*) floor);
	d3_RebuildFloorMeshes((char*) floor);
	*(unsigned char*) ((char*) floor + 0x8036) |= 1;
}
