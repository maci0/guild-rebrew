#include "Develop/DieGildeAddOn/game/game_data.h"

// SIZE 0x3dc
struct SCENE_CONTEXT_SLOT {
	int p;
	char pad[0x3d8];
};

extern char tp_ch_PathGrid[];



void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_FreeQuadtreeNode(int);
void __cdecl d3_ClearSceneState(void);
void __cdecl gv_Free3Fields(int);

void __cdecl d3_ClearAllSceneContexts(void)
{
	int i;

	d3_SelectSceneContext(0, 0);
	if (g_773dd8 != 0) {
		d3_FreeQuadtreeNode(g_773dd8);
		g_773dd8 = 0;
	}
	d3_ClearSceneState();
	for (i = 0; i < 0x2dc; i++) {
		if (((signed char*)init_SceneContextIndices)[i] > 0) {
			d3_SelectSceneContext(((signed char*)init_SceneContextIndices)[i], 0);
			d3_ClearSceneState();
			((signed char*)init_SceneContextIndices)[i] = -1;
		}
	}
	for (i = 0; i < 0x22; i++) {
		if (d3_BuildingCategorySceneIndices[i] > 0) {
			d3_SelectSceneContext(d3_BuildingCategorySceneIndices[i], 0);
			d3_ClearSceneState();
			d3_BuildingCategorySceneIndices[i] = -1;
		}
	}
	for (i = 0; i < 64; i++) {
		if (((struct SCENE_CONTEXT_SLOT*)tp_ch_PathGrid)[i].p != 0) {
			gv_Free3Fields(((struct SCENE_CONTEXT_SLOT*)tp_ch_PathGrid)[i].p);
			((struct SCENE_CONTEXT_SLOT*)tp_ch_PathGrid)[i].p = 0;
		}
	}
}
