

#include <math.h>

extern int d3_SceneRenderLock;
extern float g_1040d00[0x400];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_6b8700;
extern void* d3_ActiveLights;
extern int d3_MaxLightListCount;
extern int d3_LightSortCount;
extern void* d3_LightSortList;
extern char g_67bc38[];
extern char g_67bc28[];

void* __cdecl m_alloc(int, void*);

/* ADDRESS: GOLDDE 0x00446650 */
void __cdecl d3_InitLightBuffers(int nlist, int nactive)
{
	int i;

	d3_SceneRenderLock = 0;
	for (i = 0; i < 0x400; i++) {
		g_1040d00[i] = 1.0f - (float) acos(i * 0.0009765625f) * 0.63661975f;
	}
	d3_MaxActiveLights = nactive;
	g_6b8700 = 0;
	d3_ActiveLights = m_alloc(nactive * 12, g_67bc38);
	d3_MaxLightListCount = nlist;
	d3_LightSortCount = 0;
	d3_LightSortList = m_alloc(nlist * 12, g_67bc28);
}
