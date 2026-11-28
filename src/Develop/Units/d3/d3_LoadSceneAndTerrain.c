#include "Develop/DieGildeAddOn/game/game_data.h"

// SIZE 0x8038
struct D3_FLOOR_HEADER {
	int kind;
	char pad[0x8032];
	unsigned char lo : 2;
	unsigned char mode : 3;
};

extern int d3_CurrentFloor;
extern char tp_ch_PathGrid[];
extern char g_699b08;
extern int d3_ActiveScene;



void __cdecl d3_SelectSceneContext(int, int);
void __cdecl d3_DisposeSceneContext(int);
#include "Develop/Units/d3/client_scene_loader.h"
int __cdecl d3sm_CreateMap(struct D3_FLOOR_HEADER*, int, int);
void __cdecl d3_TraverseSceneObjects(int, int, int, void*);
void __cdecl d3_BindBuildingSceneObjects(void);
void __cdecl d3_ClearSceneObjectActiveFlag(void);

int __cdecl d3_LoadSceneAndTerrain(void* stream)
{
	int save;

	d3_SelectSceneContext(1, 0);
	d3_DisposeSceneContext(0);
	d3_SelectSceneContext(0, 0);
	d3_LoadScene(0, stream, d2_UpdateSceneLoadProgress);
	d3_SelectSceneContext(1, 0);
	d3_SelectSceneContext(0, 0);
	if (((struct D3_FLOOR_HEADER*)d3_CurrentFloor)->kind == 0x80) {
		(*(int*)tp_ch_PathGrid) = d3sm_CreateMap(((struct D3_FLOOR_HEADER*)d3_CurrentFloor), 0x100, 2);
	} else if (((struct D3_FLOOR_HEADER*)d3_CurrentFloor)->kind == 0x40) {
		(*(int*)tp_ch_PathGrid) = d3sm_CreateMap(((struct D3_FLOOR_HEADER*)d3_CurrentFloor), 0x80, 2);
	} else {
		(*(int*)tp_ch_PathGrid) = d3sm_CreateMap(((struct D3_FLOOR_HEADER*)d3_CurrentFloor), 0x100, 2);
	}
	save = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 0);
	if (((struct D3_FLOOR_HEADER*)d3_CurrentFloor) != 0) {
		((struct D3_FLOOR_HEADER*)d3_CurrentFloor)->mode = g_699b08;
	}
	d3_TraverseSceneObjects(d3_ActiveScene, 0, 0x1c0, (void*) d3_BindBuildingSceneObjects);
	d3_TraverseSceneObjects(d3_ActiveScene, 0, 0xc0, (void*) d3_ClearSceneObjectActiveFlag);
	d3_SelectSceneContext(save, 0);
	return 1;
}
