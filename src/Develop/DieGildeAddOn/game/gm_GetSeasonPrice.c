#include "Develop/DieGildeAddOn/game/season_slots.h"


#include "Develop/DieGildeAddOn/game/game_data.h"

float __cdecl eval_ObjektPreis2Credits(int, int);

/* ADDRESS: GOLDDE 0x004f6b90 */
float __cdecl gm_GetSeasonPrice(int id, unsigned char a)
{
	int i;

	for (i = 0; i < 0x55; i++) {
		if (((MARKET_STOCK_SLOT*)(gm_MarketStockTable + a * 0x2a90))[i].objekt_id == id) {
			return ((MARKET_STOCK_SLOT*)(gm_MarketStockTable + a * 0x2a90))[i].price;
		}
	}
	return eval_ObjektPreis2Credits(id, 100);
}
