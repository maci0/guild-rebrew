#include "Develop/DieGildeAddOn/game/entity_record.h"


extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"

void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, int, int);

void __cdecl d2_GrantTutorialCh5Reward(int a)
{
	char* p;

	p = ((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970]);
	if (a == 0) {
		cm_RequestChangeBits(*(int*)&((ENTITY_RECORD_VIEW*)p)->entity_id, 0x1c8, 4, 0x4000, 0);
		cm_RequestTransferCurrencyNoKill(*(int*)&((ENTITY_RECORD_VIEW*)p)->entity_id, -1, 0, 0x3e80);
	}
}
