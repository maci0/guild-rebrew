extern int d3_ActiveScene;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d3_CurrentFloor;

char __cdecl d3_InvalidateNodeRenderCacheCallback(void* p, int arg);
void __cdecl d3_VisitSceneObjects(int list, int a, int mask, char(__cdecl* fn)(void*, int), int arg);
void __cdecl d3_ResetSkyDomeNormals(int a, int b);

/* ADDRESS: GOLDTL 0x00438af0 */
/* ADDRESS: GOLDDE 0x00431cd0 */
void __cdecl d3_InvalidateSceneRenderCache(unsigned char a)
{
	d3_VisitSceneObjects(d3_ActiveScene, 0, 0x1ff, d3_InvalidateNodeRenderCacheCallback, a);
	if (g_6b89c0 != 0) {
		d3_ResetSkyDomeNormals(g_6b89c0, 0);
	}
	if (((char*)d3_CurrentFloor) != 0) {
		((char*)d3_CurrentFloor)[0x8036] |= 1;
	}
}
