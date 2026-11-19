extern int g_67a370;
#include "Develop/DieGildeAddOn/game/game_data.h"


void __cdecl d3_TraverseSceneObjects(int, int, int, void (__cdecl*)(void));
void __cdecl fcn_00514d80(void);
void __cdecl fcn_00454560(int);
int __cdecl fcn_00454c00(int, int, int, int);
#include "client_lighting.h"

void __cdecl fcn_00514e30(void)
{
	d3_TraverseSceneObjects(g_67a370, 0, 0xc0, fcn_00514d80);
	if (g_773dd8) {
		fcn_00454560(g_773dd8);
		g_773dd8 = fcn_00454c00(0, 0x40, 8, 7);
	}
	UpdateSceneLighting(1);
}
