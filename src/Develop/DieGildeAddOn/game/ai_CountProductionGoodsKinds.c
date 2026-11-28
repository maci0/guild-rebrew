typedef struct Rec {
	char type;
	char rest[0x40];
} Rec;
// SIZE 0x41
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/production_goods.h"
#include "Develop/DieGildeAddOn/game/goods_plan.h"





// SIZE 0x58

extern char* lpObjektePROT;
#include "Develop/client_types.h"
 

/* ADDRESS: GOLDTL 0x00487d80 */
void __cdecl ai_CountProductionGoodsKinds(int* ca, int* cb, PRODUCTION_GOODS_RECORD* n)
{
	int i;
	GOODS_PLAN_ENTRY* s;

	if (!(n->flags & 1)) {
		if ((*(char *)&((OBJECT_PROTOTYPE*)lpObjektePROT)[n->goods_id].kind) == 0x17 || (*(char *)&((OBJECT_PROTOTYPE*)lpObjektePROT)[n->goods_id].kind) == 0x25) {
			(*ca)++;
		} else {
			(*cb)++;
		}
		n->flags |= 1;
	}
	for (i = 0; i < 4; i++) {
		if (n->building_indices[i] < 0) {
			continue;
		}
		s = &ai_ResourceRequests[n->building_indices[i]];
		if (!(s->flags & 1)) {
			if ((*(char *)&((OBJECT_PROTOTYPE*)lpObjektePROT)[s->goods_id].kind) == 0x17 || (*(char *)&((OBJECT_PROTOTYPE*)lpObjektePROT)[s->goods_id].kind) == 0x25) {
				(*ca)++;
			} else {
				(*cb)++;
			}
			s->flags |= 1;
			if (s->parent_index != -1) {
				((PRODUCTION_GOODS_RECORD*)ai_ProductionGoodsPlans)[s->parent_index].flags |= 1;
			}
		}
		if (s->parent_index != -1) {
			ai_CountProductionGoodsKinds(ca, cb, &((PRODUCTION_GOODS_RECORD*)ai_ProductionGoodsPlans)[s->parent_index]);
		}
	}
}
