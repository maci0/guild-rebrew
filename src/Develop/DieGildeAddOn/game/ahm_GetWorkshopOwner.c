#include "Develop/DieGildeAddOn/game/building_prototype.h"


typedef struct
{
	char type;
	char pad[0x24c];
} Tile;
// SIZE 0x24d

extern unsigned char* lpGebaeudePROT;

void* __cdecl gm_LookupEntityRecordById(int);

/* ADDRESS: GOLDDE 0x004d8c20 */
void* __cdecl ahm_GetWorkshopOwner(unsigned char* building)
{
	int* idPtr;

	if (((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[building[0]].category)) == 0x1e) {
		idPtr = *(int**) (building + 0x65);
		if (idPtr != 0) {
			return gm_LookupEntityRecordById(*idPtr);
		}
	}
	return 0;
}
