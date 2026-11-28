


#include "Develop/DieGildeAddOn/game/alchemy_player_prototype.h"

extern ALCHEMY_DRAW_SLOT g_772f90[3];

void __cdecl ahm_ClearDrawSlot(ALCHEMY_DRAW_SLOT* slot)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (&g_772f90[i] == slot) {
			g_772f90[i].active = 0;
			return;
		}
	}
}
