#include "Develop/DieGildeAddOn/game/entity_record.h"


extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"

void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c51a0(int, int, int, int);

void __cdecl fcn_0057fe50(int a)
{
	char* p;

	p = ((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[g_774970]);
	if (a == 0) {
		fcn_004c5420(*(int*)&((ENTITY_RECORD_VIEW*)p)->entity_id, 0x1c8, 4, 0x4000, 0);
		fcn_004c51a0(*(int*)&((ENTITY_RECORD_VIEW*)p)->entity_id, -1, 0, 0x3e80);
	}
}
