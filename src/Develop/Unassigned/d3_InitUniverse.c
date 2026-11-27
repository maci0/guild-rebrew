

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67a370;
extern int g_6b8300;
extern int* g_6b89e4;
extern char g_67a448[];

int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl d3_RebuildFloorMeshes(int);
void __cdecl fcn_0043f6a0(int);
void __cdecl d3sm_Rebuild(int, int);

char __cdecl d3_InitUniverse(int flags)
{
	char buf[0x100];

	fcn_0064d41a(buf, g_67a448, g_6b8008, g_67a370, d3_CurrentContextIndex, g_6b8058, flags);
	if (g_6b8300 != 0) {
		d3_RebuildFloorMeshes(g_6b8300);
		if ((flags & 2) != 0) {
			fcn_0043f6a0(g_6b8300);
		}
	}
	g_6b8058 = ~flags & 3;
	if (g_6b8058 == 0 && (*(int*)&g_6b89e4) != 0 && g_6b8300 == 0) {
		d3sm_Rebuild((*(int*)&g_6b89e4), 0);
	}
	return 1;
}
