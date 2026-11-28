#include "Develop/DieGildeAddOn/game/building_prototype.h"


typedef struct
{
	char type;
	char pad[0x24c];
} Tile;
// SIZE 0x24d

extern unsigned char* lpGebaeudePROT;

/* ADDRESS: GOLDDE 0x004c23a0 */
int __cdecl cut_GetBuildingCombatType(unsigned char* building)
{
	BUILDING_PROTOTYPE * tile;

	tile = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[building[0]];
	if (((char) tile->category) == 0x13) {
		return 0;
	}
	if (((char) tile->category) == 0x10) {
		return 1;
	}
	return ((char) tile->category) == 4 ? 2 : 0;
}
