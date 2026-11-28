


#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_player.h"

void __cdecl cm_RequestTransferCurrencyNoKill(int, int, int, int);

void __cdecl d2_GrantTutorialGold(int a)
{
	if (a == 0) {
		cm_RequestTransferCurrencyNoKill(*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id, -1, 0, 0x2bc0);
	}
}
