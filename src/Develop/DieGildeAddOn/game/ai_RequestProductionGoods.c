#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/production_goods.h"
// SIZE 0x58

#include "Develop/DieGildeAddOn/game/game_data.h"
 

void __cdecl cm_RequestClearLagerslot(int, int);


/* ADDRESS: GOLDTL 0x0047e220 */
void __cdecl ai_RequestProductionGoods(char* x)
{
	int i;

	for (i = 0; i < g_100b0ac; i++) {
		if (g_100d0c0[i].unk_3c == 0 && (g_100d0c0[i].flags & 8) == 0)
			cm_RequestClearLagerslot(*(int*) (x + 2), g_100d0c0[i].goods_id);
	}
}
