#include <stdlib.h>
#include <string.h>
#include "octree.h"

extern COLOR_OCTREE_NODE* g_6b6f20[6];
extern unsigned char d3_OctreePalette[3][0x100];
extern unsigned short g_6b5e08[256];
extern unsigned short g_6b6b18[256];
extern unsigned short g_6b6d20[256];

int __cdecl d3_FindNearestPaletteColor(int r, int g, int b);

/* ADDRESS: GOLDTL 0x0041c470 */
unsigned int __cdecl d3_QuantizeImagePixels(unsigned char* input, char* output, int width, int height, int dither)
{
	unsigned int i;
	unsigned int count;
	unsigned char* map;
	unsigned char* clamp;
	short* cache;
	int entries;
	int size;
	short* a;
	short* b;
	char* error;
	int row;
	int reverse;
	int step;
	short* down;
	short* up;
	int x;
	int r;
	int g;
	int bl;
	unsigned int key;
	int index;
	int dr;
	int dg;
	int db;
	unsigned char* clamp_mid;

	i = 0;
	if (!dither) {
		count = (unsigned int)width * height;
		map = (unsigned char*)malloc(32768);
		if (!map) {
			return 0;
		}
		for (; i < 32768; i++) {
			if (g_6b6f20[5][i].count) {
				map[i] = (unsigned char)d3_FindNearestPaletteColor(
				    (unsigned char)((i >> 7) & 128) | (unsigned char)((unsigned char)(i & 4) * 2) | ((unsigned char)(i >> 1) & 16) | ((unsigned char)(i >> 3) & 32) | ((unsigned char)(i >> 5) & 64),
				    (unsigned char)((i >> 6) & 128) | (unsigned char)((i >> 4) & 64) | (unsigned char)((i >> 2) & 32) | (unsigned char)((unsigned char)(i & 2) << 2) | ((unsigned char)i & 16),
				    (unsigned char)(((unsigned char)(i & 1) << 2 | (unsigned char)(i & 8)) * 2) | ((unsigned char)(i >> 1) & 32) | ((unsigned char)(i >> 3) & 64) | ((unsigned char)(i >> 5) & 128));
			}
		}
		for (i = 0; i < count; i++, input += 3) {
			output[i] = map[g_6b6d20[input[0]] + g_6b5e08[input[1]] + g_6b6b18[input[2]]];
		}
		free(map);
		return 1;
	}
	reverse = 0;
	entries = width * 3 + 6;
	clamp = (unsigned char*)malloc(768);
	clamp_mid = clamp + 256;
	cache = (short*)malloc(65536);
	size = entries * 2;
	a = (short*)malloc(size);
	b = (short*)malloc(size);
	error = (char*)malloc(512);
	if (clamp && cache && a && b && error) {
		if (entries > 0) {
			for (x = 0; x < entries; x++) {
				a[x] = 0;
			}
		}
		memset(cache, 255, 65536);
		for (x = 0; x < 256; x++) {
			clamp_mid[x - 256] = 0;
			clamp_mid[x] = (unsigned char)x;
			clamp_mid[x + 256] = 255;
		}
		for (x = 0; x < 256; x++) {
			error[x] = -20;
			error[256 + x] = 20;
		}
		for (x = -20; x <= 20; x++) {
			error[256 + x] = (char)x;
		}
		for (row = 0; row < height; row++) {
			if (reverse) {
				step = -1;
				input += width * 3 - 3;
				output += width - 1;
				up = b + 3;
				down = a + width * 3;
			} else {
				step = 1;
				up = a + 3;
				down = b + width * 3;
			}
			down[2] = 0;
			down[1] = 0;
			down[0] = 0;
			for (x = width; x > 0; x--) {
				r = clamp_mid[input[0] + ((up[0] + 8) >> 4)];
				g = clamp_mid[input[1] + ((up[1] + 8) >> 4)];
				bl = clamp_mid[input[2] + ((up[2] + 8) >> 4)];
				key = (((r & 248) << 5) | (g & 248)) << 2 | (bl >> 3);
				if (cache[key] < 0) {
					cache[key] = (short)d3_FindNearestPaletteColor(r, g, bl);
				}
				up += 3;
				down -= 3;
				*output = *(unsigned char*)&cache[key];
				index = cache[key];
				dr = (error + 256)[r - d3_OctreePalette[0][index]];
				dg = (error + 256)[g - d3_OctreePalette[1][index]];
				db = (error + 256)[bl - d3_OctreePalette[2][index]];
				down[0] = (short)dr;
				down[6] += (short)(dr * 3);
				down[3] += (short)(dr * 5);
				up[0] += (short)(dr * 7);
				down[1] = (short)dg;
				down[7] += (short)(dg * 3);
				down[4] += (short)(dg * 5);
				up[1] += (short)(dg * 7);
				down[2] = (short)db;
				down[8] += (short)(db * 3);
				down[5] += (short)(db * 5);
				up[2] += (short)(db * 7);
				input += step * 3;
				output += step;
			}
			if (row % 2 == 1) {
				input += (width + 1) * 3;
				output += width + 1;
			}
			reverse = !reverse;
		}
		free(clamp);
		free(cache);
		free(a);
		free(b);
		free(error);
		return 1;
	}
	if (clamp) {
		free(clamp);
	}
	if (cache) {
		free(cache);
	}
	if (a) {
		free(a);
	}
	if (b) {
		free(b);
	}
	if (error) {
		free(error);
	}
	return 0;
}
