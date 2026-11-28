


#include "Develop/DieGildeAddOn/game/alchemy_player_prototype.h"

extern int g_772f78;
extern int g_772f7c;
extern int g_772f80;
extern int g_772f84;
extern int g_772f88;
extern ALCHEMY_DRAW_SLOT ahm_DrawSlots[3];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern ALCHEMY_PLAYER_PROTOTYPE* ahm_PlayerPrototypes;

void __cdecl ahm_ResetAlchemyState(int a);

/* ADDRESS: GOLDDE 0x004d8e30 */
void __cdecl ahm_DealPlayerPrototypes(void)
{
	int i;

	if (ahm_PlayerPrototypeCount == 0) {
		return;
	}
	for (i = 0; i < 3; i++) {
		ahm_DrawSlots[i].v = ahm_PlayerPrototypes[g_772f88 % ahm_PlayerPrototypeCount];
		g_772f88++;
		ahm_DrawSlots[i].active = 1;
		ahm_DrawSlots[i].x = g_772f80;
		ahm_DrawSlots[i].y = g_772f78;
		g_772f80 = (g_772f84 + g_772f80) % 25;
		g_772f78 = (g_772f7c + g_772f78) % 25;
	}
	if (g_772f88 >= ahm_PlayerPrototypeCount) {
		ahm_ResetAlchemyState(1);
	}
}
