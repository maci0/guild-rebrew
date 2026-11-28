

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d3_ActiveScene;
extern int d3_CurrentFloor;
extern int* d3_InteriorSupermap;
extern char g_67a448[];

int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl d3_RebuildFloorMeshes(int);
void __cdecl fcn_0043f6a0(int);
void __cdecl d3sm_Rebuild(int, int);

char __cdecl d3_InitUniverse(int flags)
{
	char buf[0x100];

	fcn_0064d41a(buf, g_67a448, g_6b8008, d3_ActiveScene, d3_CurrentContextIndex, g_6b8058, flags);
	if (d3_CurrentFloor != 0) {
		d3_RebuildFloorMeshes(d3_CurrentFloor);
		if ((flags & 2) != 0) {
			fcn_0043f6a0(d3_CurrentFloor);
		}
	}
	g_6b8058 = ~flags & 3;
	if (g_6b8058 == 0 && (*(int*)&d3_InteriorSupermap) != 0 && d3_CurrentFloor == 0) {
		d3sm_Rebuild((*(int*)&d3_InteriorSupermap), 0);
	}
	return 1;
}
