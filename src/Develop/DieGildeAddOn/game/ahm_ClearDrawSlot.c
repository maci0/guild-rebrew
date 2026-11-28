


#include "Develop/DieGildeAddOn/game/alchemy_player_prototype.h"

extern ALCHEMY_DRAW_SLOT ahm_DrawSlots[3];

void __cdecl ahm_ClearDrawSlot(ALCHEMY_DRAW_SLOT* slot)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (&ahm_DrawSlots[i] == slot) {
			ahm_DrawSlots[i].active = 0;
			return;
		}
	}
}
