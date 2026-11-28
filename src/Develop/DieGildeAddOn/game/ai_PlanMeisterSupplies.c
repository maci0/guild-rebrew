#include "Develop/DieGildeAddOn/game/goods_plan.h"
#include "Develop/DieGildeAddOn/game/ai_supply_candidate.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
#define MAX(a, b) ((a) < (b) ? (b) : (a))
extern int ai_ArmorGoodsIds[];
extern int ai_WeaponGoodsIds[];
extern int g_86805c;

char* __cdecl gm_QueryEntities(void* id, int a, int b, int c);
int __cdecl gm_CollectItemSuppliers(int id);

/* ADDRESS: GOLDTL 0x00486c40 */
void __cdecl ai_PlanMeisterSupplies(ENTITY_RECORD* entity, unsigned int unused, int budget)
{
	char* q;
	int i;
	int j;
	int k;
	int found;
	int sum;

	(void) unused;
	for (i = 0; i < 768; i++) {
		if (((ENTITY_RECORD*) gm_EntitySlotTable)[i].entity_index != 0xffff &&
		    ((ENTITY_RECORD*) gm_EntitySlotTable)[i].unk_16c == entity->unk_16c &&
		    ((ENTITY_RECORD*) gm_EntitySlotTable)[i].unk_165[0] != 0) {
			q = gm_QueryEntities(((ENTITY_RECORD*) gm_EntitySlotTable)[i].object_list, 1, 4, 0xc);
			if (q == 0) {
				for (k = 0; k < ai_ResourceCount; k++) {
					if (ai_ResourceRequests[k].goods_id == ai_WeaponGoodsIds[0]) {
						ai_ResourceRequests[k].requested++;
						ai_ResourceRequests[k].flags |= 2;
						break;
					}
				}
			} else {
				found = 0;
				j = 0;
				while (!found) {
					if (ai_WeaponGoodsIds[j] == 0 || ai_WeaponGoodsIds[j + 1] == 0) {
						break;
					}
					ai_WeaponGoodsIds[j] = *(unsigned short*) q;
					if (ai_WeaponGoodsIds[j] != 0) {
						for (k = 0; !found && k < ai_ResourceCount; k++) {
							if (ai_ResourceRequests[k].goods_id == ai_WeaponGoodsIds[j + 1]) {
								ai_ResourceRequests[k].requested++;
								ai_ResourceRequests[k].flags |= 2;
								found = 1;
							}
						}
					}
					j++;
				}
				if (!found) {
					j = 0;
					while (!found) {
						if (ai_ArmorGoodsIds[j] == 0 || ai_ArmorGoodsIds[j + 1] == 0) {
							break;
						}
						ai_ArmorGoodsIds[j] = *(unsigned short*) q;
						if (ai_ArmorGoodsIds[j] != 0) {
							for (k = 0; !found && k < ai_ResourceCount; k++) {
								if (ai_ResourceRequests[k].goods_id == ai_ArmorGoodsIds[j + 1]) {
									ai_ResourceRequests[k].requested++;
									ai_ResourceRequests[k].flags |= 2;
									found = 1;
								}
							}
						}
						j++;
					}
				}
			}
		}
	}
	for (i = 0; i < ai_ResourceCount; i++) {
		if (ai_ResourceRequests[i].requested != 0) {
			found = 0;
			k = 0;
			while (!found) {
				if (ai_WeaponGoodsIds[k] == 0) {
					break;
				}
				if (ai_ResourceRequests[i].goods_id == ai_WeaponGoodsIds[k]) {
					ai_ResourceRequests[i].requested -= ai_ResourceRequests[i].stock + ai_ResourceRequests[i].allocated;
					ai_ResourceRequests[i].requested = MAX(ai_ResourceRequests[i].requested, 0);
					found = 1;
				}
				k++;
			}
			if (!found) {
				k = 0;
				while (!found) {
					if (ai_ArmorGoodsIds[k] == 0) {
						break;
					}
					if (ai_ResourceRequests[i].goods_id == ai_ArmorGoodsIds[k]) {
						ai_ResourceRequests[i].requested -= ai_ResourceRequests[i].stock + ai_ResourceRequests[i].allocated;
						ai_ResourceRequests[i].requested = MAX(ai_ResourceRequests[i].requested, 0);
						found = 1;
					}
					k++;
				}
			}
			if (ai_ResourceRequests[i].requested != 0) {
				gm_CollectItemSuppliers(ai_ResourceRequests[i].goods_id);
				found = 0;
				for (k = 0; !found && k < g_86805c; k++) {
					if (g_868c40[k].unk_08 != 0 && g_868c40[k].limit >= 1) {
						ai_ResourceRequests[i].supplier = g_868c40[k].entity;
					}
				}
			}
			if (ai_ResourceRequests[i].supplier == 0) {
				ai_ResourceRequests[i].requested = 0;
			}
		}
	}
	sum = 0;
	for (k = 0; ai_WeaponGoodsIds[k] != 0; k++) {
		for (i = 0; i < ai_ResourceCount; i++) {
			if (ai_WeaponGoodsIds[k] == ai_ResourceRequests[i].goods_id && ai_ResourceRequests[i].requested != 0) {
				while (ai_ResourceRequests[i].requested > 0 &&
				       ai_ResourceRequests[i].requested * ai_ResourceRequests[i].price + (float) sum > (float) budget) {
					ai_ResourceRequests[i].requested--;
				}
				sum = (int) (ai_ResourceRequests[i].requested * ai_ResourceRequests[i].price + sum);
			}
		}
	}
	for (k = 0; ai_ArmorGoodsIds[k] != 0; k++) {
		for (i = 0; i < ai_ResourceCount; i++) {
			if (ai_ArmorGoodsIds[k] == ai_ResourceRequests[i].goods_id && ai_ResourceRequests[i].requested != 0) {
				while (ai_ResourceRequests[i].requested > 0 &&
				       ai_ResourceRequests[i].requested * ai_ResourceRequests[i].price + (float) sum > (float) budget) {
					ai_ResourceRequests[i].requested--;
				}
				sum = (int) (ai_ResourceRequests[i].requested * ai_ResourceRequests[i].price + sum);
			}
		}
	}
}
unsigned char _dpad_100df20[2048];
