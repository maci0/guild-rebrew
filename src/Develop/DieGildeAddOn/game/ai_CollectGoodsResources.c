
// Collects the goods ids of the two id lists (0x100e760, 0x100e720) into the
// segment table, then adds each production record's stock to the matching
// segments. The second list prices its entries by the first list's id at the
// same index.

#include "Develop/DieGildeAddOn/game/goods_plan.h"

typedef struct Stats {
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats;
// SIZE 0xb8

#include "Develop/DieGildeAddOn/game/game_data.h"
extern int ai_ArmorGoodsIds[];
extern int ai_WeaponGoodsIds[];
extern unsigned char gm_ActiveTownIndex;

float __cdecl gm_GetSeasonPrice(int id, unsigned char k);
int __cdecl gm_GetMsgObjektField(char* b, int id);
int __cdecl gm_eval_SlotVoll(char*, int, int);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_FindRecordById(int);
int __cdecl gm_CalcEntityInventoryStats(char* e, Stats* s);

/* ADDRESS: GOLD 0x486180 */
void __cdecl ai_CollectGoodsResources(char* a, char* b)
{
	int i;
	int j;
	int k;
	int m;
	int found;
	unsigned short id;
	char* e;
	char* r;
	Stats st;

	for (j = 0; ai_WeaponGoodsIds[j] != 0; j++) {
		for (i = 0; i < ai_ResourceCount; i++) {
			if (ai_ResourceRequests[i].goods_id == ai_WeaponGoodsIds[j]) {
				break;
			}
		}
		if (i >= ai_ResourceCount) {
			ai_ResourceRequests[ai_ResourceCount].goods_id = ai_WeaponGoodsIds[j];
			ai_ResourceRequests[ai_ResourceCount].parent_index = -1;
			ai_ResourceRequests[ai_ResourceCount].supplier = 0;
			ai_ResourceRequests[ai_ResourceCount].unk_10 = 0;
			ai_ResourceRequests[ai_ResourceCount].requested = 0;
			ai_ResourceRequests[ai_ResourceCount].unk_18 = 0;
			ai_ResourceRequests[ai_ResourceCount].price = gm_GetSeasonPrice(ai_WeaponGoodsIds[j], gm_ActiveTownIndex);
			ai_ResourceRequests[ai_ResourceCount].allocated = 0;
			ai_ResourceRequests[ai_ResourceCount].stock = 0;
			ai_ResourceRequests[ai_ResourceCount].state_30 = 0x81;
			ai_ResourceRequests[ai_ResourceCount].flags = 0;
			ai_ResourceRequests[ai_ResourceCount].stock = gm_GetMsgObjektField(b, ai_WeaponGoodsIds[j]);
			ai_ResourceRequests[ai_ResourceCount].capacity = gm_eval_SlotVoll(b, ai_WeaponGoodsIds[j], 1000000);
			ai_ResourceCount++;
		}
	}
	for (j = 0; ai_ArmorGoodsIds[j] != 0; j++) {
		for (i = 0; i < ai_ResourceCount; i++) {
			if (ai_ResourceRequests[i].goods_id == ai_ArmorGoodsIds[j]) {
				break;
			}
		}
		if (i >= ai_ResourceCount) {
			ai_ResourceRequests[ai_ResourceCount].goods_id = ai_ArmorGoodsIds[j];
			ai_ResourceRequests[ai_ResourceCount].parent_index = -1;
			ai_ResourceRequests[ai_ResourceCount].supplier = 0;
			ai_ResourceRequests[ai_ResourceCount].unk_10 = 0;
			ai_ResourceRequests[ai_ResourceCount].requested = 0;
			ai_ResourceRequests[ai_ResourceCount].unk_18 = 0;
			ai_ResourceRequests[ai_ResourceCount].price = gm_GetSeasonPrice(ai_WeaponGoodsIds[j], gm_ActiveTownIndex);
			ai_ResourceRequests[ai_ResourceCount].allocated = 0;
			ai_ResourceRequests[ai_ResourceCount].stock = 0;
			ai_ResourceRequests[ai_ResourceCount].state_30 = 0x81;
			ai_ResourceRequests[ai_ResourceCount].flags = 0;
			ai_ResourceRequests[ai_ResourceCount].stock = gm_GetMsgObjektField(b, ai_ArmorGoodsIds[j]);
			ai_ResourceRequests[ai_ResourceCount].capacity = gm_eval_SlotVoll(b, ai_ArmorGoodsIds[j], 1000000);
			ai_ResourceCount++;
		}
	}
	for (e = he_StartHandlungSearch(2, 0, 0xb, 3, *(int*) (*(char**) (a + 0x16c) + 1)); e != 0; e = he_fn_Handlung()) {
		r = gm_FindRecordById(*(int*) (e + 0xac));
		if (r == 0) {
			continue;
		}
		gm_CalcEntityInventoryStats(r, &st);
		for (k = 0; k < st.x0; k++) {
			id = st.x48[k];
			if (id == 0) {
				continue;
			}
			found = 0;
			for (m = 0; found == 0 && m < 3; m++) {
				if (((unsigned short*) (e + 0xd0))[m] == id) {
					found = 1;
				}
			}
			if (found == 0) {
				for (i = 0; i < ai_ResourceCount; i++) {
					if (id == ai_ResourceRequests[i].goods_id) {
						ai_ResourceRequests[i].allocated += st.x68[k];
					}
				}
			}
		}
		for (m = 0; m < 3; m++) {
			if (((unsigned short*) (e + 0xd6))[m] != 0) {
				for (i = 0; i < ai_ResourceCount; i++) {
					if (((unsigned short*) (e + 0xd6))[m] == ai_ResourceRequests[i].goods_id) {
						ai_ResourceRequests[i].allocated += ((int*) (e + 0xdc))[m];
					}
				}
			}
		}
	}
}
