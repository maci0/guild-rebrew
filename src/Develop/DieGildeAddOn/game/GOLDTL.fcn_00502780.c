#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/season_slots.h"


float __cdecl fcn_005025a0(int, int);

float __cdecl gm_CalcMarketSlotPriceByObjektId(int a, int id)
{
	int i;

	for (i = 0; i < 0x55; i++) {
		if (((MARKET_STOCK_SLOT*)(g_85ab90 + a * 0x2a90))[i].objekt_id == id) {
			return fcn_005025a0(a, i);
		}
	}
	return -1.0f;
}
