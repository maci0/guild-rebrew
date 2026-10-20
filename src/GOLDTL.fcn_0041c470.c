#include <stdlib.h>
#include <string.h>
#include "octree.h"

extern OctNode* g_6b6f20[6];
extern unsigned char g_6b6008[3][0x100];
extern unsigned short g_6b5e08[256];
extern unsigned short g_6b6b18[256];
extern unsigned short g_6b6d20[256];

int __cdecl fcn_0041ca10(int r, int g, int b);

/* ADDRESS: GOLDTL 0x0041c470 */
unsigned int __cdecl fcn_0041c470(unsigned char* input, char* output, int width, unsigned int height, int dither)
{
	unsigned int i;
	unsigned int count;
	unsigned char* map;
	unsigned char* clamp;
	short* cache;
	unsigned int entries;
	unsigned int size;
	short* a;
	short* b;
	char* error;
	unsigned int row;
	int reverse;
	int step;
	short* next;
	short* current;
	short* down;
	short* up;
	int x;
	unsigned int r;
	unsigned int g;
	unsigned int bl;
	unsigned int key;
	unsigned int index;
	int dr;
	int dg;
	int db;

	i = 0;
	if (!dither) {
		count = (unsigned int)width * height;
		map = (unsigned char*)malloc(32768);
		if (!map) {
			return 0;
		}
		for (; i < 32768; i++) {
			if (g_6b6f20[5][i].count) {
				r = ((i >> 7) & 128) | ((i & 4) * 2) | ((i >> 1) & 16) | ((i >> 3) & 32) | ((i >> 5) & 64);
				g = ((i >> 6) & 128) | ((i >> 4) & 64) | ((i >> 2) & 32) | ((i & 2) << 2) | (i & 16);
				bl = (((i & 1) << 2 | (i & 8)) * 2) | ((i >> 1) & 32) | ((i >> 3) & 64) | ((i >> 5) & 128);
				map[i] = (unsigned char)fcn_0041ca10(r, g, bl);
			}
		}
		for (i = 0; i < count; i++, input += 3) {
			output[i] = map[g_6b6d20[input[0]] + g_6b5e08[input[1]] + g_6b6b18[input[2]]];
		}
		free(map);
		return 1;
	}
	clamp = (unsigned char*)malloc(768);
	cache = (short*)malloc(65536);
	entries = (unsigned int)width * 3 + 6;
	size = entries * 2;
	a = (short*)malloc(size);
	b = (short*)malloc(size);
	error = (char*)malloc(512);
	if (clamp && cache && a && b && error) {
		if ((int)entries > 0) {
			memset(a, 0, entries * 2);
		}
		memset(cache, 255, 65536);
		for (i = 0; i < 256; i++) {
			clamp[i] = 0;
			clamp[256 + i] = (unsigned char)i;
			clamp[512 + i] = 255;
		}
		for (i = 0; i < 256; i++) {
			error[i] = -20;
			error[256 + i] = 20;
		}
		for (x = -20; x <= 20; x++) {
			error[256 + x] = (char)x;
		}
		reverse = 0;
		for (row = 0; (int)row < (int)height; row++) {
			step = reverse ? -1 : 1;
			if (reverse) {
				input += (unsigned int)width * 3 - 3;
				output += (unsigned int)width - 1;
			}
			next = reverse ? a : b;
			current = reverse ? b : a;
			down = next + (unsigned int)width * 3;
			down[0] = 0;
			down[1] = 0;
			down[2] = 0;
			up = current + 3;
			for (x = width; x != 0; x--) {
				r = clamp[256 + (unsigned int)input[0] + ((up[0] + 8) >> 4)];
				g = clamp[256 + (unsigned int)input[1] + ((up[1] + 8) >> 4)];
				bl = clamp[256 + (unsigned int)input[2] + ((up[2] + 8) >> 4)];
				key = (((r & 248) << 5) | (g & 248)) << 2 | (bl >> 3);
				if (cache[key] < 0) {
					cache[key] = (short)fcn_0041ca10(r, g, bl);
				}
				index = (unsigned short)cache[key];
				*output = (unsigned char)index;
				dr = error[256 + r - g_6b6008[0][index]];
				dg = error[256 + g - g_6b6008[1][index]];
				db = error[256 + bl - g_6b6008[2][index]];
				down[0] = (short)dr;
				down[6] = (short)(down[6] + dr * 3);
				down[3] = (short)(down[3] + dr * 5);
				up[0] = (short)(up[0] + dr * 7);
				down[1] = (short)dg;
				down[7] = (short)(down[7] + dg * 3);
				down[4] = (short)(down[4] + dg * 5);
				up[1] = (short)(up[1] + dg * 7);
				down[2] = (short)db;
				down[8] = (short)(down[8] + db * 3);
				down[5] = (short)(down[5] + db * 5);
				up[2] = (short)(up[2] + db * 7);
				input += step * 3;
				output += step;
				down -= 3;
				up += 3;
			}
			if (row % 2) {
				input += ((unsigned int)width + 1) * 3;
				output += (unsigned int)width + 1;
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
