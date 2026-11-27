

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_67a370;
extern int g_6b8300;
extern char g_67a42c[];

int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_0043f690(int);
void __cdecl d3_ReleaseTerrainSurfaces(int);

char __cdecl d3_DeinitUniverse(int flags)
{
	char buf[0x100];

	fcn_0064d41a(buf, g_67a42c, g_6b8008, g_67a370, d3_CurrentContextIndex, g_6b8058, flags);
	if (g_6b8300 != 0) {
		if ((flags & 2) != 0) {
			fcn_0043f690(g_6b8300);
		}
		d3_ReleaseTerrainSurfaces(g_6b8300);
	}
	g_6b8058 = flags;
	return 1;
}
