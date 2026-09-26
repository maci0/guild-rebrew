// FUNCTION: GOLD 0x00420db0
// SIZE: 189
// FUNCTION: GOLDTL 0x0041c3b0
// SIZE: 189

#include "octree.h"

extern OctNode* g_6b6f20[6];
extern int g_6b6308;
extern unsigned char g_6b6008[3][0x100];

void __cdecl fcn_0041c3b0(int n, int level)
{
	int i;
	unsigned int cnt;
	unsigned int gg;
	unsigned int bb;
	OctNode* p;

	if (g_6b6f20[level][n].mask != 0) {
		for (i = 7; i >= 0; i--) {
			if (g_6b6f20[level][n].mask & (1 << i)) {
				fcn_0041c3b0(n * 8 + i, level + 1);
			}
		}
	}
	p = &g_6b6f20[level][n];
	if (p->count != 0) {
		p->idx = (unsigned char) g_6b6308;
		cnt = g_6b6f20[level][n].count;
		gg = g_6b6f20[level][n].g;
		bb = g_6b6f20[level][n].b;
		g_6b6008[0][g_6b6308] = (unsigned char) ((g_6b6f20[level][n].r + cnt / 2) / cnt);
		g_6b6008[1][g_6b6308] = (unsigned char) ((cnt / 2 + gg) / cnt);
		g_6b6008[2][g_6b6308++] = (unsigned char) ((cnt / 2 + bb) / cnt);
	}
}
