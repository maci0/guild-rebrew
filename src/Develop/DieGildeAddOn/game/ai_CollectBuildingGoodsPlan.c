/*
 * Collects the goods a building needs into the object record table
 * (g_100d0c0), prices them, and ranks them.
 */
#include <string.h>
#include "Develop/DieGildeAddOn/game/goods_plan.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
/* g_100d0c0: 0x58-byte object records. */
#pragma pack(push, 1)
#include "production_goods.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"





















/* Statistics block filled by fcn_0050de80. */
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

/* g_868050: 0x24d-byte level records. */
typedef struct Lvl {
	unsigned char kind;   /* 0x000 */
	char pad1[0x24c];
} Lvl;
#pragma pack(pop)

 
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* lpObjektePROT;
extern char* lpGebaeudePROT;
extern float g_664124;

char* __cdecl gm_QueryEntities(int, int, int, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl he_fn_Handlung(void);
char* __cdecl gm_FindRecordById(int);
int __cdecl gm_GetMsgField(char*, char*);
int __cdecl gm_eval_SlotVoll(char*, int, int);
int __cdecl gm_CalcEntityInventoryStats(char*, Stats*);
int __cdecl gm_GetBuildingTechEffect(char*, int, int);
void __cdecl cm_RequestClearLagerslot(int, int);
void __cdecl ai_CalcProductionGoodProfit(PRODUCTION_GOODS_RECORD*);

/* ADDRESS: GOLDTL 0x004849b0 */
void __cdecl ai_CollectBuildingGoodsPlan(char* entity, char* prod, char* craft)
{
	Stats st;
	PRODUCTION_GOODS_RECORD tmp;
	char* goodsSlot;
	char* action;
	char* actor;
	int i;
	int j;
	int k;
	int found;
	unsigned short id;
	unsigned char kind;

	ai_ProductionGoodsCount = 0;
	goodsSlot = gm_QueryEntities(*(int*) (prod + 0x14), 1, 5);
	while (goodsSlot != 0) {
		if (*(int*) (goodsSlot + 0xe)  > 1 && ai_ProductionGoodsCount < 0x20) {
			ai_ProductionGoodsPlans[ai_ProductionGoodsCount].goods_id = *(unsigned short*) goodsSlot;
			for (j = 0; j < 4; j++) {
				ai_ProductionGoodsPlans[ai_ProductionGoodsCount].building_indices[j] = -1;
			}
			ai_ProductionGoodsPlans[ai_ProductionGoodsCount].min_1 = 0;
			ai_ProductionGoodsPlans[ai_ProductionGoodsCount].min_2 = 0;
			ai_ProductionGoodsPlans[ai_ProductionGoodsCount].value = -1.0e10f;
			ai_ProductionGoodsPlans[ai_ProductionGoodsCount].amount = 0;
			ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_3c = 0;
			ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_40 = 0;
			ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_44 = 0;
			ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_48 = 0x21;
			ai_ProductionGoodsPlans[ai_ProductionGoodsCount].flags = 0;
			ai_ProductionGoodsCount++;
		}
		goodsSlot = gm_NextEntityQueryMatch();
	}

	ai_ResourceCount = 0;
	for (i = 0; i < ai_ProductionGoodsCount; i++) {
		for (j = 0; j < 4; j++) {
			if (((OBJECT_PROTOTYPE *)lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].ingredient_ids[j] != 0) {
				for (k = 0; k < ai_ResourceCount; k++) {
					if (ai_ResourceRequests[k].goods_id == ((OBJECT_PROTOTYPE *)lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].ingredient_ids[j]) {
						ai_ProductionGoodsPlans[i].building_indices[j] = k;
						break;
					}
				}
				if (ai_ProductionGoodsPlans[i].building_indices[j] == -1) {
					if (ai_ResourceCount >= 0x80) {
						return;
					}
					ai_ResourceRequests[ai_ResourceCount].goods_id = ((OBJECT_PROTOTYPE *)lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].ingredient_ids[j];
					ai_ResourceRequests[ai_ResourceCount].parent_index = -1;
					ai_ResourceRequests[ai_ResourceCount].supplier = 0;
					ai_ResourceRequests[ai_ResourceCount].unk_10 = 0;
					ai_ResourceRequests[ai_ResourceCount].requested = 0;
					ai_ResourceRequests[ai_ResourceCount].unk_18 = 0;
					ai_ResourceRequests[ai_ResourceCount].price = -1.0e10f;
					ai_ResourceRequests[ai_ResourceCount].allocated = 0;
					ai_ResourceRequests[ai_ResourceCount].stock = 0;
					ai_ResourceRequests[ai_ResourceCount].state_30 = 0x21;
					ai_ResourceRequests[ai_ResourceCount].flags = 0;
					ai_ProductionGoodsPlans[i].building_indices[j] = ai_ResourceCount;
					ai_ResourceCount++;
				}
			}
		}
	}

	kind = ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) *(char**) (entity + 0x16c)].category;
	if (kind == 0xe || kind == 8 || kind == 0x20) {
		for (i = 0; i < ai_ResourceCount; i++) {
			if (ai_ResourceRequests[i].goods_id == 0x1c7 || ai_ResourceRequests[i].goods_id == 0x1c4 ||
			    ai_ResourceRequests[i].goods_id == 0x1c5 || ai_ResourceRequests[i].goods_id == 0x1c6 ||
			    ai_ResourceRequests[i].goods_id == 0x2af || ai_ResourceRequests[i].goods_id == 0x2b0) {
				ai_ResourceRequests[i].flags |= 0x24;
				for (k = 0; k < ai_ProductionGoodsCount; k++) {
					if (ai_ProductionGoodsPlans[k].goods_id == ai_ResourceRequests[i].goods_id) {
						ai_ProductionGoodsPlans[k].flags |= 0x24;
						break;
					}
				}
				if (k >= ai_ProductionGoodsCount) {
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].goods_id = ai_ResourceRequests[i].goods_id;
					for (j = 0; j < 4; j++) {
						ai_ProductionGoodsPlans[ai_ProductionGoodsCount].building_indices[j] = -1;
					}
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].min_1 = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].min_2 = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].value = -1.0e10f;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].amount = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_3c = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_40 = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_44 = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_48 = 0x21;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].flags = 0x24;
					ai_ProductionGoodsCount = ai_ProductionGoodsCount + 1;
				}
			}
			if (ai_ResourceRequests[i].goods_id == 0x1c1 || ai_ResourceRequests[i].goods_id == 0x1c2 ||
			           ai_ResourceRequests[i].goods_id == 0x1c3) {
				ai_ResourceRequests[i].flags |= 0x204;
				for (k = 0; k < ai_ProductionGoodsCount; k++) {
					if (ai_ProductionGoodsPlans[k].goods_id == ai_ResourceRequests[i].goods_id) {
						ai_ProductionGoodsPlans[k].flags |= 0x204;
						break;
					}
				}
				if (k >= ai_ProductionGoodsCount) {
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].goods_id = ai_ResourceRequests[i].goods_id;
					for (j = 0; j < 4; j++) {
						ai_ProductionGoodsPlans[ai_ProductionGoodsCount].building_indices[j] = -1;
					}
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].min_1 = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].min_2 = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].value = -1.0e10f;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].amount = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_3c = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_40 = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_44 = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_48 = 0x21;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].flags = 0x204;
					ai_ProductionGoodsCount = ai_ProductionGoodsCount + 1;
				}
			}
		}
	}

	kind = ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) *(char**) (entity + 0x16c)].category;
	if (kind == 0x1d || kind == 0x1f) {
		for (i = 0; i < ai_ResourceCount; i++) {
			if (ai_ResourceRequests[i].goods_id == 0x225 || ai_ResourceRequests[i].goods_id == 0x226 || ai_ResourceRequests[i].goods_id == 0x227 ||
			    ai_ResourceRequests[i].goods_id == 0x293 || ai_ResourceRequests[i].goods_id == 0x294 || ai_ResourceRequests[i].goods_id == 0x295) {
				ai_ResourceRequests[i].flags |= 0x404;
				for (k = 0; k < ai_ProductionGoodsCount; k++) {
					if (ai_ProductionGoodsPlans[k].goods_id == ai_ResourceRequests[i].goods_id) {
						ai_ProductionGoodsPlans[k].flags |= 0x404;
						break;
					}
				}
				if (k >= ai_ProductionGoodsCount) {
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].goods_id = ai_ResourceRequests[i].goods_id;
					for (j = 0; j < 4; j++) {
						ai_ProductionGoodsPlans[ai_ProductionGoodsCount].building_indices[j] = -1;
					}
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].min_1 = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].min_2 = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].value = -1.0e10f;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].amount = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_3c = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_40 = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_44 = 0;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].unk_48 = 0x21;
					ai_ProductionGoodsPlans[ai_ProductionGoodsCount].flags = 0x404;
					ai_ProductionGoodsCount = ai_ProductionGoodsCount + 1;
				}
			}
		}
	}

	for (i = 0; i < ai_ResourceCount; i++) {
		for (k = 0; k < ai_ProductionGoodsCount; k++) {
			if (ai_ResourceRequests[i].goods_id == ai_ProductionGoodsPlans[k].goods_id) {
				ai_ResourceRequests[i].parent_index = k;
				break;
			}
		}
	}

	for (i = 0; i < ai_ProductionGoodsCount; i++) {
		goodsSlot = gm_QueryEntities(*(int*) (craft + 0x14), 1, 0, ai_ProductionGoodsPlans[i].goods_id);
		if (goodsSlot == 0) {
			ai_ProductionGoodsPlans[i].unk_3c = 0;
		} else {
			ai_ProductionGoodsPlans[i].unk_3c = gm_GetMsgField(craft, goodsSlot);
		}
		ai_ProductionGoodsPlans[i].unk_40 =
		    gm_eval_SlotVoll(craft, ai_ProductionGoodsPlans[i].goods_id, 0xf4240);
	}

	for (i = 0; i < ai_ResourceCount; i++) {
		goodsSlot = gm_QueryEntities(*(int*) (craft + 0x14), 1, 0, ai_ResourceRequests[i].goods_id);
		if (goodsSlot == 0) {
			ai_ResourceRequests[i].stock = 0;
		} else {
			ai_ResourceRequests[i].stock = gm_GetMsgField(craft, goodsSlot);
			if (ai_ResourceRequests[i].stock == 0) {
				cm_RequestClearLagerslot(*(int*) (craft + 2), ai_ResourceRequests[i].goods_id);
			}
		}
		ai_ResourceRequests[i].capacity =
		    gm_eval_SlotVoll(craft, ai_ResourceRequests[i].goods_id, 0xf4240);
	}

	for (action = he_StartHandlungSearch(2, 0, 0xb, 3,
	                     *(int*) (*(char**) (entity + 0x16c) + 1));
	     action != 0;
	     action = he_fn_Handlung()) {
		actor = gm_FindRecordById(*(int*) (action + 0xac));
		if (actor == 0) {
			continue;
		}
		gm_CalcEntityInventoryStats(actor, &st);
		for (i = 0; i < st.x0; i++) {
			id = st.x48[i];
			if (id == 0) {
				continue;
			}
			found = 0;
			for (j = 0; found == 0 && j < 3; j++) {
				if (((unsigned short*) (action + 0xd0))[j] == id) {
					found = 1;
				}
			}
			if (found != 0) {
				continue;
			}
			for (j = 0; j < ai_ProductionGoodsCount; j++) {
				if (id == ai_ProductionGoodsPlans[j].goods_id) {
					ai_ProductionGoodsPlans[j].amount += st.x68[i];
				}
			}
			for (j = 0; j < ai_ResourceCount; j++) {
				if (id == ai_ResourceRequests[j].goods_id) {
					ai_ResourceRequests[j].allocated += st.x68[i];
				}
			}
		}
		for (j = 0; j < 3; j++) {
			if (((unsigned short*) (action + 0xd6))[j] != 0) {
				for (i = 0; i < ai_ProductionGoodsCount; i++) {
					if (((unsigned short*) (action + 0xd6))[j] == ai_ProductionGoodsPlans[i].goods_id) {
						ai_ProductionGoodsPlans[i].amount += ((int*) (action + 0xdc))[j];
					}
				}
				for (i = 0; i < ai_ResourceCount; i++) {
					if (((unsigned short*) (action + 0xd6))[j] == ai_ResourceRequests[i].goods_id) {
						ai_ResourceRequests[i].allocated += ((int*) (action + 0xdc))[j];
					}
				}
			}
		}
	}

	kind = ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) *(char**) (entity + 0x16c)].category;
	if (kind == 8 || kind == 0xe) {
		for (action = he_StartHandlungSearch(2, 0, 0x14, 3,
		                     *(int*) (*(char**) (entity + 0x16c) + 1));
		     action != 0;
		     action = he_fn_Handlung()) {
			for (i = 0; i < ai_ResourceCount; i++) {
				if (ai_ResourceRequests[i].goods_id !=
				    (int) *(unsigned short*) (action + 0xae)) {
					continue;
				}
				ai_ResourceRequests[i].allocated =
				    (int) (((float) gm_GetBuildingTechEffect(*(char**) (entity + 0x16c), 0xb, 1) * 0.01f + 1.0f) *
				               g_664124 +
				           (float) ai_ResourceRequests[i].allocated);
			}
		}
	}

	kind = ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) *(char**) (entity + 0x16c)].category;
	if (kind == 8) {
		for (action = he_StartHandlungSearch(2, 0, 0x15, 3,
		                     *(int*) (*(char**) (entity + 0x16c) + 1));
		     action != 0;
		     action = he_fn_Handlung()) {
			for (i = 0; i < ai_ResourceCount; i++) {
				if (ai_ResourceRequests[i].goods_id !=
				    (int) *(unsigned short*) (action + 0xae)) {
					continue;
				}
				ai_ResourceRequests[i].allocated =
				    (int) (((float) gm_GetBuildingTechEffect(*(char**) (entity + 0x16c), 0xb, 1) * 0.01f + 1.0f) *
				               g_664124 +
				           (float) ai_ResourceRequests[i].allocated);
			}
		}
	}

	kind = ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) *(char**) (entity + 0x16c)].category;
	if (kind == 0x1d || kind == 0x1f) {
		for (action = he_StartHandlungSearch(2, 0, 0x8c, 3,
		                     *(int*) (*(char**) (entity + 0x16c) + 1));
		     action != 0;
		     action = he_fn_Handlung()) {
			for (i = 0; i < ai_ResourceCount; i++) {
				if (ai_ResourceRequests[i].goods_id !=
				    (int) *(unsigned short*) (action + 0xac)) {
					continue;
				}
				ai_ResourceRequests[i].allocated =
				    (int) (((float) gm_GetBuildingTechEffect(*(char**) (entity + 0x16c), 0xb, 1) * 0.01f + 1.0f) *
				               g_664124 +
				           (float) ai_ResourceRequests[i].allocated);
			}
		}
	}

	for (i = 0; i < ai_ProductionGoodsCount; i++) {
		ai_CalcProductionGoodProfit(&ai_ProductionGoodsPlans[i]);
	}

	for (i = 0; i < ai_ProductionGoodsCount; i++) {
		for (j = i; j < ai_ProductionGoodsCount; j++) {
			if (ai_ProductionGoodsPlans[i].slope < ai_ProductionGoodsPlans[j].slope) {
				tmp = ai_ProductionGoodsPlans[i];
				ai_ProductionGoodsPlans[i] = ai_ProductionGoodsPlans[j];
				ai_ProductionGoodsPlans[j] = tmp;
			}
		}
	}

	for (i = 0; i < ai_ResourceCount; i++) {
		if (ai_ResourceRequests[i].parent_index != -1) {
			for (j = 0; j < ai_ProductionGoodsCount; j++) {
				if (ai_ResourceRequests[i].goods_id == ai_ProductionGoodsPlans[j].goods_id) {
					ai_ResourceRequests[i].flags |= 0x40;
					ai_ProductionGoodsPlans[j].flags |= 0x40;
					ai_ResourceRequests[i].parent_index = j;
				}
			}
		}
	}

	for (i = 0; i < ai_ProductionGoodsCount; i++) {
		ai_ProductionGoodsPlans[i].unk_48 = i;
	}
}
unsigned char _dpad_100af80[320];
unsigned char _dpad_100b0c0[8192];
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_100d0c0[2884];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_100d0c4[48];
unsigned char _dpad_100d0f8[20];
unsigned char _dpad_100d114[2732];
#endif
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_100d0c4[48];
unsigned char _dpad_100d0f8[20];
unsigned char _dpad_100d114[2732];
#endif
