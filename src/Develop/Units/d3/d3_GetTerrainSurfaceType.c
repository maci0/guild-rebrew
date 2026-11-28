#include <string.h>

extern int* d3_CachedTerrainMap;
extern int d3_TerrainLayerSurfaceTypes[8];
extern char d3_TerrainSurfaceNames[15][9];

/* GOLD twin of GOLDTL fcn_0045a2e0: the name strings sit at img + 0x1a64
 * instead of 0x7e24. */


int __cdecl d3_GetTerrainSurfaceType(int x, int y, int* img)
{
	int off;
	int k;
	int i;

	off = (img[0] - 1 & y) * img[0] + (img[0] - 1 & x);
	if ((((unsigned char*) img[5])[off] & 0x80) != 0) {
		return 0;
	}
	if (d3_CachedTerrainMap != img) {
		for (k = 0; k < 8; k++) {
			d3_TerrainLayerSurfaceTypes[k] = 1;
			if (((char*) img)[0x1a64 + k * 0x40] != 0) {
				for (i = 0; i < 15; i++) {
					if (strstr(_strupr((char*) img + 0x1a64 + k * 0x40), d3_TerrainSurfaceNames[i]) != 0) {
						d3_TerrainLayerSurfaceTypes[k] = i;
						break;
					}
				}
			}
		}
		d3_CachedTerrainMap = img;
	}
	return d3_TerrainLayerSurfaceTypes[((unsigned char*) img[5])[off]];
}
