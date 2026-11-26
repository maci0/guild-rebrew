#include "Develop/DieGildeAddOn/game/spiel.h"
#include "Develop/DieGildeAddOn/game/game_data.h"




int __cdecl fcn_0050e520(int, int*);

void __cdecl gm_CollectGebaeudeUpgrades(unsigned char* e)
{
	int t;
	int v;

	t = gm_GetBuildingTypeCategory(*e);
	if (t == 3) {
		g_7746f8 = 1;
		return;
	}
	if (t == 5 && fcn_0050e520(*e, &v)) {
		g_7746f8 = v;
	}
}
