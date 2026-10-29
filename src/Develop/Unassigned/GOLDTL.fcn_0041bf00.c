


#include "octree.h"

extern OctNode* g_6b6f20[6];
extern OctRef* g_6b6f40;
extern void* g_6b6f44;
void __cdecl free(void* p);

void __cdecl fcn_0041bf00(void)
{
	if (g_6b6f20[0] != 0) {
		free(g_6b6f20[0]);
	}
	if (g_6b6f20[1] != 0) {
		free(g_6b6f20[1]);
	}
	if (g_6b6f20[2] != 0) {
		free(g_6b6f20[2]);
	}
	if (g_6b6f20[3] != 0) {
		free(g_6b6f20[3]);
	}
	if (g_6b6f20[4] != 0) {
		free(g_6b6f20[4]);
	}
	if (g_6b6f20[5] != 0) {
		free(g_6b6f20[5]);
	}
	if (g_6b6f40 != 0) {
		free(g_6b6f40);
	}
	if (g_6b6f44 != 0) {
		free(g_6b6f44);
	}
}
