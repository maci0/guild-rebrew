#include "Develop/DieGildeAddOn/game/game_data.h"

// SIZE 0x3dc
struct SCENE_CONTEXT_SLOT {
	int p;
	char pad[0x3d8];
};

extern char g_1043370[];



void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_FreeQuadtreeNode(int);
void __cdecl fcn_00442e30(void);
void __cdecl gv_Free3Fields(int);

void __cdecl d3_ClearAllSceneContexts(void)
{
	int i;

	d3_SelectSceneContext(0, 0);
	if (g_773dd8 != 0) {
		d3_FreeQuadtreeNode(g_773dd8);
		g_773dd8 = 0;
	}
	fcn_00442e30();
	for (i = 0; i < 0x2dc; i++) {
		if (((signed char*)init_SceneContextIndices)[i] > 0) {
			d3_SelectSceneContext(((signed char*)init_SceneContextIndices)[i], 0);
			fcn_00442e30();
			((signed char*)init_SceneContextIndices)[i] = -1;
		}
	}
	for (i = 0; i < 0x22; i++) {
		if (g_7f3b00[i] > 0) {
			d3_SelectSceneContext(g_7f3b00[i], 0);
			fcn_00442e30();
			g_7f3b00[i] = -1;
		}
	}
	for (i = 0; i < 64; i++) {
		if (((struct SCENE_CONTEXT_SLOT*)g_1043370)[i].p != 0) {
			gv_Free3Fields(((struct SCENE_CONTEXT_SLOT*)g_1043370)[i].p);
			((struct SCENE_CONTEXT_SLOT*)g_1043370)[i].p = 0;
		}
	}
}
