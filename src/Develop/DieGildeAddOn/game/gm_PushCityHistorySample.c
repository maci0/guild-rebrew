

#include <string.h>

typedef struct
{
	int a;
	int b;
	int c;
	int d;
	int e;
} CITY_HISTORY_SAMPLE;
// SIZE 0x14

#include "Develop/client_types.h"
extern GRAPH_SAMPLE g_99ec20[16];
extern int g_99f5e4;
extern int g_99f5e8;
extern int g_99f5ec;
extern int g_99f604;
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLD 0x4f88c0 */

void __cdecl gm_PushCityHistorySample(void)
{
	memmove(((CITY_HISTORY_SAMPLE*)g_99ec20), ((CITY_HISTORY_SAMPLE*)g_99ec20) + 1, 15 * sizeof(CITY_HISTORY_SAMPLE));
	((CITY_HISTORY_SAMPLE*)g_99ec20)[15].a = g_99f5e4;
	((CITY_HISTORY_SAMPLE*)g_99ec20)[15].b = g_99f5e8;
	((CITY_HISTORY_SAMPLE*)g_99ec20)[15].c = g_99f5ec;
	((CITY_HISTORY_SAMPLE*)g_99ec20)[15].d = g_99f604;
	((CITY_HISTORY_SAMPLE*)g_99ec20)[15].e = (int) g_773d4c;
}
