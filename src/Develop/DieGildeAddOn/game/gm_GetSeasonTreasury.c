#include "Develop/DieGildeAddOn/game/game_data.h"



void* __cdecl gm_QueryEntities(int, int, int, ...);

/* ADDRESS: GOLDDE 0x004f80b0 */
int __cdecl gm_GetSeasonTreasury(char* entity, char season)
{
	int result;
	char* r;

	result = 0;
	r = gm_QueryEntities(*(int*) (entity + 0x178), 1, result, (int) (unsigned short) ((int*)g_8680b4)[season * 189]);
	if (r) {
		result = *(int*) (r + 0xe);
	}
	return result;
}
