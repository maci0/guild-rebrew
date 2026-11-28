

#include "Develop/DieGildeAddOn/game/alchemy_player_prototype.h"

#include "Develop/DieGildeAddOn/game/game_data.h"
extern ALCHEMY_PLAYER_PROTOTYPE* ahm_PlayerPrototypes;
extern int g_772fe0;
extern ALCHEMY_RECIPE_PROTOTYPE* ahm_RecipePrototypes;

void __cdecl m_FreeTracked(int);

/* ADDRESS: GOLDDE 0x004da130 */
void __cdecl ahm_FreeAlchemyPrototypes(void)
{
	if (ahm_PlayerPrototypes != 0) {
		m_FreeTracked((int) ahm_PlayerPrototypes);
		ahm_PlayerPrototypes = 0;
	}
	if (ahm_RecipePrototypes != 0) {
		m_FreeTracked((int) ahm_RecipePrototypes);
		ahm_RecipePrototypes = 0;
	}
	g_772fe0 = 0;
	ahm_PlayerPrototypeCount = 0;
}
