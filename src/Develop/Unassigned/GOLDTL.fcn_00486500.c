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

float __cdecl fcn_0050bb50(int id, unsigned char k);
float __cdecl fcn_0050b840(int id);

/* ADDRESS: GOLDTL 0x00486500 */
void __cdecl fcn_00486500(PRODUCTION_GOODS_RECORD* n)
{
	GOODS_PLAN_ENTRY* s;
	int i;

	if (!(n->value > -10000000000.0)) {
		n->sum = 0;
		for (i = 0; i < 4; i++) {
			if (n->building_indices[i] >= 0) {
				s = &g_100b0c0[n->building_indices[i]];
				if (!(s->price > -10000000000.0)) {
					if (s->parent_index != -1) {
						s->price = (float)(fcn_0050bb50(s->goods_id, g_773d75) * 0.9);
					} else {
						s->price = fcn_0050bb50(s->goods_id, g_773d75);
					}
				}
				n->sum += ((OBJECT_PROTOTYPE*)lpObjektePROT)[n->goods_id].ingredient_amounts[i] * s->price;
			}
		}
		n->sum = n->sum / ((OBJECT_PROTOTYPE*)lpObjektePROT)[n->goods_id].value_036;
		n->base = fcn_0050b840(n->goods_id);
		n->value = n->base + n->sum;
		n->price = fcn_0050bb50(n->goods_id, g_773d75);
		n->slope = (n->price - n->value) / ((OBJECT_PROTOTYPE*)lpObjektePROT)[n->goods_id].value_022;
	}
}
