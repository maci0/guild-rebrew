#include "octree.h"

extern COLOR_OCTREE_NODE* g_6b6f20[6];
extern OctRef* g_6b6f40;
extern unsigned int g_6b6f38;

void __cdecl d3_SiftDownOctreeHeap();

/* ADDRESS: GOLDTL 0x0041c290 */
void __cdecl d3_ReduceOctreeColors(unsigned int limit)
{
	unsigned char lvl;
	unsigned char lvl1;
	unsigned int idx;
	unsigned int i8;

	if (g_6b6f38 <= limit) {
		return;
	}
	do {
		lvl = g_6b6f40[1].lvl;
		lvl1 = (unsigned char)(lvl - 1);
		idx = g_6b6f40[1].idx;
		i8 = idx >> 3;
		if (g_6b6f20[lvl1][i8].count != 0) {
			g_6b6f40[1] = g_6b6f40[g_6b6f38];
			g_6b6f38--;
		} else {
			g_6b6f40[1].lvl = lvl1;
			g_6b6f40[1].idx = (unsigned short)(idx >> 3);
		}
		g_6b6f20[lvl1][i8].count += g_6b6f20[lvl][idx].count;
		g_6b6f20[lvl1][i8].r += g_6b6f20[lvl][idx].r;
		g_6b6f20[lvl1][i8].g += g_6b6f20[lvl][idx].g;
		g_6b6f20[lvl1][i8].b += g_6b6f20[lvl][idx].b;
		g_6b6f20[lvl1][i8].mask &= ~(1 << (idx & 7));
		d3_SiftDownOctreeHeap(1);
	} while (g_6b6f38 > limit);
}
