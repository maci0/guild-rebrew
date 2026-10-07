// FUNCTION: GOLD 0x00420870
// FUNCTION: GOLDTL 0x0041be70

#include "octree.h"

extern OctNode* g_6b6f20[6];
extern int g_6b6308;
void* __cdecl fcn_0064de9d(int n, int size);

int __cdecl fcn_0041be70(void)
{
	OctNode** p;

	g_6b6f20[0] = fcn_0064de9d(0x18, 1);
	g_6b6f20[1] = fcn_0064de9d(0x18, 8);
	g_6b6f20[2] = fcn_0064de9d(0x18, 0x40);
	g_6b6f20[3] = fcn_0064de9d(0x18, 0x200);
	g_6b6f20[4] = fcn_0064de9d(0x18, 0x1000);
	g_6b6f20[5] = fcn_0064de9d(0x18, 0x8000);
	for (p = g_6b6f20; (int) p <= (int) &g_6b6f20[5]; p++) {
		if (*p == 0) {
			return 0;
		}
	}
	g_6b6308 = 0;
	return 1;
}
