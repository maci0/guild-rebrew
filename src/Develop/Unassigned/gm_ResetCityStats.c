


#include <string.h>

#pragma intrinsic(memcpy, memset)

#include "client_types.h"
extern Rec24_99f5a0 g_99f5a0;
extern char g_99f6a0[];
extern char g_99f620[];
extern CRIME_GRID_CELL g_99ef80[9][8];
extern GRAPH_SAMPLE g_99ec20[16];
extern char g_99f5e0[];
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl gm_ResetCityStats(void)
{
	memset(&g_99f5a0, 0, 36);
	memset(g_99f6a0, 0, 340);
	memset(g_99f620, 0, 104);
	memset(((char*)g_99ef80), 0, 1536);
	memset(((char*)g_99ec20), 0, 320);
	memset(g_99f5e0, 0, 40);
	g_99f5a0.head = -1;
	(*(int*)&g_773d4c) = 0;
}
