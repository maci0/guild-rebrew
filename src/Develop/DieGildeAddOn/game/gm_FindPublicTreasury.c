#include "Develop/DieGildeAddOn/game/client_actions.h"

char* __cdecl gm_GetGuildHall(int);
void* __cdecl gm_QueryEntities(int, int, int, ...);

char* __cdecl gm_FindPublicTreasury(int building_slot)
{
	char* building;

	building = gm_GetGuildHall(building_slot);
	if (building_slot == 1) {
		return gm_QueryEntities(*(int*) (building + 0x5d), 2, 6, 0, 0x115);
	} else {
		return gm_QueryEntities(*(int*) (building + 0x5d), 2, 6, 0, 0x142);
	}
}
