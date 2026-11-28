#include "Develop/DieGildeAddOn/game/entity_record.h"


extern char gm_EntitySlotTable[];

/* ADDRESS: GOLDDE 0x004f89e0 */
char* __cdecl gm_FindBuildingOwner(int building)
{
	int i;
	int cursor;
	char* record;

	record = 0;
	if (building == 0) {
		return record;
	}
	i = 0;
	cursor = (int) (gm_EntitySlotTable + 2);
	while (cursor < (int) (gm_EntitySlotTable + 2 + 768 * (int)sizeof(ENTITY_RECORD))) {
		if (*(char*) (cursor + 0x162) != 0 && *(int*) (cursor + 0x16a) == building) {
			if (*(char*) cursor == 6 || *(char*) cursor == 7 || *(char*) cursor == 1 || *(char*) cursor == 2) {
				record = (char *)&((ENTITY_RECORD*)gm_EntitySlotTable)[i];
				break;
			}
		}
		cursor += (int)sizeof(ENTITY_RECORD);
		i++;
	}
	return record;
}
