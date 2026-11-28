#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/season_slots.h"


float __cdecl gm_CalcMarketSlotPrice(int, int);

float __cdecl gm_CalcMarketSlotPriceByObjektId(int a, int id)
{
	int i;

	for (i = 0; i < 0x55; i++) {
		if (((MARKET_STOCK_SLOT*)(gm_MarketStockTable + a * 0x2a90))[i].objekt_id == id) {
			return gm_CalcMarketSlotPrice(a, i);
		}
	}
	return -1.0f;
}
