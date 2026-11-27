#pragma pack(push, 1)
typedef struct Rec {
	char type;
	char pad1[0x21];
	unsigned int cap;
	unsigned short weight[4];
	char pad2e[8];
	unsigned short div;
	char pad38[9];
} Rec;
// SIZE 0x41
#pragma pack(pop)
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/production_goods.h"










#include "Develop/DieGildeAddOn/game/goods_plan.h"

extern char* lpObjektePROT;
extern unsigned char g_773d75;

float __cdecl gm_GetSeasonPrice(int id, unsigned char k);
float __cdecl gm_CalcGoodBaseValue(int id);

/* ADDRESS: GOLDTL 0x00486500 */
void __cdecl ai_CalcProductionGoodProfit(PRODUCTION_GOODS_RECORD* good)
{
	GOODS_PLAN_ENTRY* ingredient;
	int i;

	if (!(good->value > -10000000000.0)) {
		good->sum = 0;
		for (i = 0; i < 4; i++) {
			if (good->building_indices[i] >= 0) {
				ingredient = &g_100b0c0[good->building_indices[i]];
				if (!(ingredient->price > -10000000000.0)) {
					if (ingredient->parent_index != -1) {
						ingredient->price = (float)(gm_GetSeasonPrice(ingredient->goods_id, g_773d75) * 0.9);
					} else {
						ingredient->price = gm_GetSeasonPrice(ingredient->goods_id, g_773d75);
					}
				}
				good->sum += ((OBJECT_PROTOTYPE*)lpObjektePROT)[good->goods_id].ingredient_amounts[i] * ingredient->price;
			}
		}
		good->sum = good->sum / ((OBJECT_PROTOTYPE*)lpObjektePROT)[good->goods_id].value_036;
		good->base = gm_CalcGoodBaseValue(good->goods_id);
		good->value = good->base + good->sum;
		good->price = gm_GetSeasonPrice(good->goods_id, g_773d75);
		good->slope = (good->price - good->value) / ((OBJECT_PROTOTYPE*)lpObjektePROT)[good->goods_id].value_022;
	}
}
