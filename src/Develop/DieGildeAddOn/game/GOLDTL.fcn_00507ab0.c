#include "client_actions.h"

char* __cdecl gm_FindPublicBuilding(int);
void* __cdecl fcn_00502cd0(int, int, int, ...);

char* __cdecl gm_FindPublicTreasury(int building_slot)
{
	char* building;

	building = gm_FindPublicBuilding(building_slot);
	if (building_slot == 1) {
		return fcn_00502cd0(*(int*) (building + 0x5d), 2, 6, 0, 0x115);
	} else {
		return fcn_00502cd0(*(int*) (building + 0x5d), 2, 6, 0, 0x142);
	}
}
