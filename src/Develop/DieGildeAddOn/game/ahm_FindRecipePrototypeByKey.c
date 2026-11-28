


#include "Develop/DieGildeAddOn/game/alchemy_player_prototype.h"

extern int g_772fe0;
extern ALCHEMY_RECIPE_PROTOTYPE* ahm_RecipePrototypes;

ALCHEMY_RECIPE_PROTOTYPE* __cdecl ahm_FindRecipePrototypeByKey(int key)
{
	int i;

	for (i = 0; i < g_772fe0; i++) {
		if (ahm_RecipePrototypes[i].key == key) {
			return &ahm_RecipePrototypes[i];
		}
	}
	return 0;
}
