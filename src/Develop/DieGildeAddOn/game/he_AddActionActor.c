#include "Develop/DieGildeAddOn/game/entity_record.h"


extern char gm_EntitySlotTable[];

void __cdecl he_AddActionActor(int slot_idx, char* action)
{
	char* rec;
	int i;

	rec = ((char *)&((ENTITY_RECORD_VIEW *)gm_EntitySlotTable)[slot_idx]);
	for (i = 0; i < 8; i++) {
		if (*(int*) (action + 0x8c + i * 4) == *(int*)&((ENTITY_RECORD_VIEW*)rec)->entity_id) {
			break;
		}
	}
	if (i >= 8) {
		for (i = 0; i < 8; i++) {
			if (*(int*) (action + 0x8c + i * 4) == -1) {
				*(int*) (action + 0x8c + i * 4) = *(int*)&((ENTITY_RECORD_VIEW*)rec)->entity_id;
				break;
			}
		}
	}
}
