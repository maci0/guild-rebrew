#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/game_data.h"




int __cdecl gm_GetBuildingCategorySlot(int, int*);

/* ADDRESS: GOLDDE 0x00511120 */
void __cdecl gm_CollectGebaeudeUpgrades(unsigned char* e)
{
	int t;
	int v;

	t = gm_GetBuildingTypeCategory(*e);
	if (t == 3) {
		g_7746f8 = 1;
		return;
	}
	if (t == 5 && gm_GetBuildingCategorySlot(*e, &v)) {
		g_7746f8 = v;
	}
}
