#include "client_types.h"
#include "Develop/DieGildeAddOn/game/season_slots.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char g_773d75;
extern float flt_1;
extern double g_664e78;
extern double dbl_1_0;

char* __cdecl gm_FindCityItemHolder(int id);
char* __cdecl gm_FindKind47ByOwner(int owner);
char* __cdecl fcn_00502cd0(int a, int b, ...);
float __cdecl eval_ObjektPreis2Credits(int id, int arg);

/* Slot price of one season slot: stock against the slot's base rate, clamped
 * to 0.25..5 and moved 0.4 of the way from the slot's last price. */
/* ADDRESS: GOLDTL 0x005025a0 */
float __cdecl gm_CalcMarketSlotPrice(int season, int slot)
{
	char* def;
	char* store;
	char* e;
	int id;
	float stock;
	float last;
	double scale; float price;

	id = ((MARKET_STOCK_TABLE*) g_85ab80)[season].slots[slot].objekt_id;
	def = lpObjektePROT + id * 0x41;
	store = gm_FindCityItemHolder(id);
	if (store == 0 && season != g_773d75) {
		e = gm_FindKind47ByOwner(season);
		if (e != 0) {
			store = fcn_00502cd0(*(int*) (e + 0x5d), 2, 0, 0x1db, 6);
		}
	}
	stock = 0.0f;
	if (store == 0) {
		return eval_ObjektPreis2Credits(id, 100);
	}
	e = fcn_00502cd0(*(int*) (store + 0x14), 1, 0, id);
	if (e != 0) {
		stock = (float) *(int*) (e + 0xe);
	}
	last = ((MARKET_STOCK_TABLE*) g_85ab80)[season].slots[slot].price;
	scale = ((MARKET_STOCK_TABLE*) g_85ab80)[season].slots[slot].price_factor / ((MARKET_STOCK_TABLE*) g_85ab80)[season].slots[slot].basis;
	scale *= ((stock > ((MARKET_STOCK_TABLE*) g_85ab80)[season].slots[slot].basis && *def != 0x17)
			? (stock < 1.0 ? ((MARKET_STOCK_TABLE*) g_85ab80)[season].slots[slot].basis / 1.0
				: ((MARKET_STOCK_TABLE*) g_85ab80)[season].slots[slot].basis / stock)
			: flt_1);
	scale = scale > 0.25 ? scale : 0.25;
	if (scale >= g_664e78) {
		scale = 5.0;
	}
	stock = scale;
	price = ((double) eval_ObjektPreis2Credits(id, 100) * scale - (double) last) * 0.4f + ((MARKET_STOCK_TABLE*) g_85ab80)[season].slots[slot].price;
	if (((MARKET_STOCK_TABLE*) g_85ab80)[season].slots[slot].price <= 0.0f) {
		if (eval_ObjektPreis2Credits(id, 100) < 512.0f) {
			return 512.0f;
		}
		return eval_ObjektPreis2Credits(id, 100);
	}
	return price;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_7f4e51[417087];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_7f4e55[19];
unsigned char _dpad_7f4e6c[414260];
unsigned char _dpad_85a0e0[2688];
unsigned char _dpad_85ab64[28];
unsigned char _dpad_85ab88[8];
#endif
