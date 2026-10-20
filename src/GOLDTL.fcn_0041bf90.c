#include "octree.h"

extern OctNode* g_6b6f20[6];
extern OctRef* g_6b6f40;
extern unsigned int g_6b6f38;
extern unsigned short g_6b6b18[256];
extern unsigned short g_6b5e08[256];
extern unsigned short g_6b6d20[256];
void* __cdecl malloc(unsigned int size);
void __cdecl fcn_0041c190(unsigned int idx);

/* ADDRESS: GOLDTL 0x0041bf90 */
int __cdecl fcn_0041bf90(unsigned char* pixels, unsigned int count)
{
	unsigned char* p;
	unsigned int left;
	unsigned int key;
	unsigned int c;
	unsigned int i;
	unsigned int idx;
	unsigned int bit;
	OctNode** pp;

	g_6b6f40 = malloc(0x20004);
	if (!g_6b6f40) {
		return 0;
	}
	p = pixels;
	for (left = count; left > 0; left--) {
		key = g_6b6b18[p[2]];
		key += g_6b5e08[p[1]];
		key += g_6b6d20[p[0]];
		p += 3;
		g_6b6f20[5][key].count++;
	}
	g_6b6f38 = 0;
	for (i = 0; i < 0x8000; i++) {
		c = g_6b6f20[5][i].count;
		if (c) {
			g_6b6f38++;
			g_6b6f40[g_6b6f38].lvl = 5;
			g_6b6f40[g_6b6f38].idx = (unsigned short) i;
			g_6b6f20[5][i].key = c;
			g_6b6f20[5][i].r = ((((((i >> 2) & 0x1000 | i & 0x800) >> 2 | i & 0x100) >> 2 | i & 0x20) >> 1 | (i & 4) * 2) + 4) * c;
			g_6b6f20[5][i].g = (((((i >> 2) & 0x800 | i & 0x400) >> 2 | i & 0x80) >> 2 | (i & 2) << 2 | i & 0x10) + 4) * c;
			g_6b6f20[5][i].b = (((((i >> 2) & 0x400 | i & 0x200) >> 2 | i & 0x40) >> 1 | ((i & 1) << 2 | i & 8) * 2) + 4) * c;
			idx = i;
			for (pp = &g_6b6f20[4]; pp >= &g_6b6f20[0]; pp--) {
				bit = idx & 7;
				idx >>= 3;
				(*pp)[idx].key += c;
				(*pp)[idx].mask |= (unsigned char) (1 << bit);
			}
		}
	}
	for (i = g_6b6f38; i > 0; i--) {
		fcn_0041c190(i);
	}
	return 1;
}
