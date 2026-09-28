#include "../../game/entity.h"

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

// GLOBAL: SERVER 0x1002d2ec
extern char s_cm_ExSetGebUpgrade____Could_not_f[];
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Execution handler: destroys a building entity. Resolves
 * building by ID, calls gm_CleanupBuildingEntity to deallocate
 * contents, and removes it from the game world. */
// FUNCTION: GOLDTL 0x57c7b0
// SIZE: 176
// FUNCTION: SERVER 0x1000f680

int __cdecl cm_ExDestroyBuilding(int cmd, char* result)
{
	ushort* building;
	ushort* match;
	int* slot_scan;

	building = gm_StartFilteredEntitySearch(1, 1, *(int*) (cmd + 0x10));
	if (building == (ushort*) 0x0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\command\\command.c",
			0x4c32,
			"cm_ExSetGebUpgrade(): Could not find geb",
			1
		);
		return 1;
	}

	match = gm_ff_Objekt(0, 2, 7, 4, 0x1d);
	while (match != (ushort*) 0x0) {
		if (*(int*) (match + 0xe) == *(int*) ((int) building + 1)) {
			gm_RemoveEntityLink((int) match);
		}
		match = gm_NextEntityQueryMatch();
	}

	slot_scan = &g_entity_records;
	do {
		if ((ushort*) *slot_scan == building) {
			*slot_scan = 0;
		}
		slot_scan = slot_scan + 0x87;
	} while ((int) slot_scan < 0x1009ae0c);

	gm_CleanupBuildingEntity((uchar*) building);

	if (result != (char*) 0x0) {
		*result = '\x02';
		result[1] = '\0';
		*(int*) (result + 6) = 0;
	}
	return 0;
}
