

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int d3_ActiveScene;
extern int d3_CurrentFloor;
extern char g_67a42c[];

int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_0043f690(int);
void __cdecl d3_ReleaseTerrainSurfaces(int);

/* ADDRESS: GOLDDE 0x00433780 */
char __cdecl d3_DeinitUniverse(int flags)
{
	char buf[0x100];

	fcn_0064d41a(buf, g_67a42c, g_6b8008, d3_ActiveScene, d3_CurrentContextIndex, g_6b8058, flags);
	if (d3_CurrentFloor != 0) {
		if ((flags & 2) != 0) {
			fcn_0043f690(d3_CurrentFloor);
		}
		d3_ReleaseTerrainSurfaces(d3_CurrentFloor);
	}
	g_6b8058 = flags;
	return 1;
}
