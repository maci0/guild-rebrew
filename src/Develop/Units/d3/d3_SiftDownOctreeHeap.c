

#include "octree.h"

extern COLOR_OCTREE_NODE* g_6b6f20[6];
extern OctRef* g_6b6f40;
extern unsigned int g_6b6f38;

/* ADDRESS: GOLDDE 0x00419e30 */
void __cdecl d3_SiftDownOctreeHeap(unsigned int half, int unused)
{
	unsigned char lvl;
	unsigned int idx;
	unsigned int key;
	unsigned int j;
	unsigned int i;

	/* the parameter slot holds the midpoint, as in the reference frame */
	i = half;
	half = g_6b6f38 >> 1;
	lvl = g_6b6f40[i].lvl;
	idx = g_6b6f40[i].idx;
	key = g_6b6f20[lvl][idx].key;
	while (i <= half) {
		j = i * 2;
		if (j < g_6b6f38 && g_6b6f20[g_6b6f40[j].lvl][g_6b6f40[j].idx].key > g_6b6f20[g_6b6f40[j + 1].lvl][g_6b6f40[j + 1].idx].key) {
			j++;
		}
		if (key <= g_6b6f20[g_6b6f40[j].lvl][g_6b6f40[j].idx].key) {
			break;
		}
		g_6b6f40[i] = g_6b6f40[j];
		i = j;
	}
	g_6b6f40[i].lvl = lvl;
	g_6b6f40[i].idx = (unsigned short) idx;
}
