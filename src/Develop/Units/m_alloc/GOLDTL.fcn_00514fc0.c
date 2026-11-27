extern int g_67a370;
#include "Develop/DieGildeAddOn/game/game_data.h"


void __cdecl d3_TraverseSceneObjects(int, int, int, void (__cdecl*)(void));
void __cdecl d3_MarkSceneObjectForQuadtree(void);
void __cdecl fcn_00454560(int);
int __cdecl d3_BuildSceneQuadtree(int, int, int, int);

void __cdecl fcn_00514fc0(void)
{
	if (g_773dd8) {
		fcn_00454560(g_773dd8);
		g_773dd8 = 0;
	}
	d3_TraverseSceneObjects(g_67a370, 0, 0x40, d3_MarkSceneObjectForQuadtree);
	g_773dd8 = d3_BuildSceneQuadtree(0, 0x40, 8, 7);
}
