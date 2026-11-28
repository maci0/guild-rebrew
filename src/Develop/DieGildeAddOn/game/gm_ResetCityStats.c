


#include <string.h>

#pragma intrinsic(memcpy, memset)

#include "Develop/client_types.h"
extern Rec24_99f5a0 gm_DisasterState;
extern char g_99f6a0[];
extern char g_99f620[];
extern CRIME_GRID_CELL gm_CrimeGrid[9][8];
extern GRAPH_SAMPLE g_99ec20[16];
extern char gm_CityStatsBuffer[];
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl gm_ResetCityStats(void)
{
	memset(&gm_DisasterState, 0, 36);
	memset(g_99f6a0, 0, 340);
	memset(g_99f620, 0, 104);
	memset(((char*)gm_CrimeGrid), 0, 1536);
	memset(((char*)g_99ec20), 0, 320);
	memset(gm_CityStatsBuffer, 0, 40);
	gm_DisasterState.head = -1;
	(*(int*)&gm_CityPopulation) = 0;
}
