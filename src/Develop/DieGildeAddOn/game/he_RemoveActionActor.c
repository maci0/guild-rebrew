


#include "Develop/DieGildeAddOn/game/entity_record.h"

void __cdecl he_RemoveActionActor(int slot_idx, char* action)
{
	char* rec;
	int i;

	rec = ((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[slot_idx]);
	for (i = 0; i < 8; i++) {
		if (*(int*) (action + 0x8c + i * 4) == *(int*) (rec + 4)) {
			*(int*) (action + 0x8c + i * 4) = -1;
			return;
		}
	}
}
