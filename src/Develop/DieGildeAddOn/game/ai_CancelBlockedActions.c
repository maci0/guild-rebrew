


typedef struct Ent {
	unsigned short id;
	char pad2[0x17c - 2];
	char* host;
	char pad180[0x21c - 0x180];
} Ent;
// SIZE 0x21c

#include "Develop/DieGildeAddOn/game/production_goods.h"




// SIZE 0x58

#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/client_types.h"
 
#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
void __cdecl he_AssignActionSlot(char* o, int a, int id, int b);

/* ADDRESS: GOLDDE 0x00476d30 */
void __cdecl ai_CancelBlockedActions(char* e, int k)
{
	char* q;
	int found;
	int i;

	for (q = he_StartHandlungSearch(2, 0, k, 3, *(int*) (*(char**) (e + 0x16c) + 1)); q != 0; q = he_fn_Handlung()) {
		found = 0;
		if (k == 4) {
			for (i = 0; i < ai_ProductionGoodsCount; i++) {
				if (ai_ProductionGoodsPlans[i].goods_id == *(unsigned short*) (q + 0xac) && !(ai_ProductionGoodsPlans[i].flags & 8)) {
					found = 1;
				}
			}
		} else if (k == 8) {
			for (i = 0; i < ai_ProductionGoodsCount; i++) {
				if (ai_ProductionGoodsPlans[i].goods_id == *(unsigned short*) (q + 0xac) && !(ai_ProductionGoodsPlans[i].flags & 0x10)) {
					found = 1;
				}
			}
		} else if (k == 3) {
			for (i = 0; i < ai_ProductionGoodsCount; i++) {
				if (ai_ProductionGoodsPlans[i].goods_id == *(unsigned short*) (q + 0xac) && !(ai_ProductionGoodsPlans[i].flags & 8)) {
					found = 1;
				}
			}
		}
		if (found) {
			for (i = 0; i < 768; i++) {
				if ((*(unsigned short*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_index) != 0xffff && (*(char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_17c) == q) {
					he_AssignActionSlot(*(char**) (e + 0x16c), 0, (*(unsigned short*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_index), 0);
				}
			}
		}
	}
}
