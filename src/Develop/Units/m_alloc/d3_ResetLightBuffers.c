extern void* d3_LightSortList;
extern int d3_LightSortCount;
extern int d3_MaxLightListCount;
extern void* d3_ActiveLights;
extern int g_6b8700;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/Units/d3/client_lighting.h"


void __cdecl m_FreeTracked(int);

void __cdecl d3_ResetLightBuffers(void)
{
	d3_LightSortCount = 0;
	d3_MaxLightListCount = 0;
	m_FreeTracked((*(int*)&d3_LightSortList));
	(*(int*)&d3_LightSortList) = 0;
	g_6b8700 = 0;
	d3_MaxActiveLights = 0;
	m_FreeTracked((*(int*)&d3_ActiveLights));
	(*(int*)&d3_ActiveLights) = 0;
	d3_SceneRenderLock = 0;
}
