

// SIZE 0xc
typedef struct D3_LIGHT_SLOT {
	int a;
	int used;
	int b;
} D3_LIGHT_SLOT;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern void* d3_ActiveLights;
extern int g_6b8700;
extern char* g_1041d00;
extern char* g_6b86e0;
extern char* d3_DirectionalLightList;
extern char* d3_SceneLightListHead;
extern char* g_6b86ec;
extern int g_6b86f0;
extern int g_6b86f4;
extern int g_6b86f8;
extern int d3_ActiveScene;

void __cdecl d3_VisitSceneObjects(int, int, int, void*, int);
void __cdecl d3_ClassifySceneLightNode(void);

/* ADDRESS: GOLDDE 0x00446890 */
void __cdecl d3_CollectSceneLights(int ctx, unsigned char mask)
{
	int i;

	for (i = 0; i < d3_MaxActiveLights; i++) {
		((D3_LIGHT_SLOT*)d3_ActiveLights)[i].used = 0;
	}
	g_6b8700 = 0;
	(*(int*)&g_1041d00) = 0;
	(*(int*)&g_6b86ec) = 0;
	(*(int*)&d3_SceneLightListHead) = 0;
	(*(int*)&d3_DirectionalLightList) = 0;
	(*(int*)&g_6b86e0) = 0;
	g_6b86f8 = 0;
	g_6b86f4 = 0;
	g_6b86f0 = 0;
	d3_VisitSceneObjects(d3_ActiveScene, 0, (mask << 4) | 0x4e, d3_ClassifySceneLightNode, ctx);
}
