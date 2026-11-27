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

char* __cdecl fcn_00502cd0(int, int, int, ...);
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

	g_100b0ac = 0;
	goodsSlot = fcn_00502cd0(*(int*) (prod + 0x14), 1, 5);
	while (goodsSlot != 0) {
		if (*(int*) (goodsSlot + 0xe)  > 1 && g_100b0ac < 0x20) {
			g_100d0c0[g_100b0ac].goods_id = *(unsigned short*) goodsSlot;
			for (j = 0; j < 4; j++) {
				g_100d0c0[g_100b0ac].building_indices[j] = -1;
			}
			g_100d0c0[g_100b0ac].min_1 = 0;
			g_100d0c0[g_100b0ac].min_2 = 0;
			g_100d0c0[g_100b0ac].value = -1.0e10f;
			g_100d0c0[g_100b0ac].amount = 0;
			g_100d0c0[g_100b0ac].unk_3c = 0;
			g_100d0c0[g_100b0ac].unk_40 = 0;
			g_100d0c0[g_100b0ac].unk_44 = 0;
			g_100d0c0[g_100b0ac].unk_48 = 0x21;
			g_100d0c0[g_100b0ac].flags = 0;
			g_100b0ac++;
		}
		goodsSlot = gm_NextEntityQueryMatch();
	}

	ai_ResourceCount = 0;
	for (i = 0; i < g_100b0ac; i++) {
		for (j = 0; j < 4; j++) {
			if (((OBJECT_PROTOTYPE *)lpObjektePROT)[g_100d0c0[i].goods_id].ingredient_ids[j] != 0) {
				for (k = 0; k < ai_ResourceCount; k++) {
					if (g_100b0c0[k].goods_id == ((OBJECT_PROTOTYPE *)lpObjektePROT)[g_100d0c0[i].goods_id].ingredient_ids[j]) {
						g_100d0c0[i].building_indices[j] = k;
						break;
					}
				}
				if (g_100d0c0[i].building_indices[j] == -1) {
					if (ai_ResourceCount >= 0x80) {
						return;
					}
					g_100b0c0[ai_ResourceCount].goods_id = ((OBJECT_PROTOTYPE *)lpObjektePROT)[g_100d0c0[i].goods_id].ingredient_ids[j];
					g_100b0c0[ai_ResourceCount].parent_index = -1;
					g_100b0c0[ai_ResourceCount].supplier = 0;
					g_100b0c0[ai_ResourceCount].unk_10 = 0;
					g_100b0c0[ai_ResourceCount].requested = 0;
					g_100b0c0[ai_ResourceCount].unk_18 = 0;
					g_100b0c0[ai_ResourceCount].price = -1.0e10f;
					g_100b0c0[ai_ResourceCount].allocated = 0;
					g_100b0c0[ai_ResourceCount].stock = 0;
					g_100b0c0[ai_ResourceCount].state_30 = 0x21;
					g_100b0c0[ai_ResourceCount].flags = 0;
					g_100d0c0[i].building_indices[j] = ai_ResourceCount;
					ai_ResourceCount++;
				}
			}
		}
	}

	kind = ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) *(char**) (entity + 0x16c)].category;
	if (kind == 0xe || kind == 8 || kind == 0x20) {
		for (i = 0; i < ai_ResourceCount; i++) {
			if (g_100b0c0[i].goods_id == 0x1c7 || g_100b0c0[i].goods_id == 0x1c4 ||
			    g_100b0c0[i].goods_id == 0x1c5 || g_100b0c0[i].goods_id == 0x1c6 ||
			    g_100b0c0[i].goods_id == 0x2af || g_100b0c0[i].goods_id == 0x2b0) {
				g_100b0c0[i].flags |= 0x24;
				for (k = 0; k < g_100b0ac; k++) {
					if (g_100d0c0[k].goods_id == g_100b0c0[i].goods_id) {
						g_100d0c0[k].flags |= 0x24;
						break;
					}
				}
				if (k >= g_100b0ac) {
					g_100d0c0[g_100b0ac].goods_id = g_100b0c0[i].goods_id;
					for (j = 0; j < 4; j++) {
						g_100d0c0[g_100b0ac].building_indices[j] = -1;
					}
					g_100d0c0[g_100b0ac].min_1 = 0;
					g_100d0c0[g_100b0ac].min_2 = 0;
					g_100d0c0[g_100b0ac].value = -1.0e10f;
					g_100d0c0[g_100b0ac].amount = 0;
					g_100d0c0[g_100b0ac].unk_3c = 0;
					g_100d0c0[g_100b0ac].unk_40 = 0;
					g_100d0c0[g_100b0ac].unk_44 = 0;
					g_100d0c0[g_100b0ac].unk_48 = 0x21;
					g_100d0c0[g_100b0ac].flags = 0x24;
					g_100b0ac = g_100b0ac + 1;
				}
			}
			if (g_100b0c0[i].goods_id == 0x1c1 || g_100b0c0[i].goods_id == 0x1c2 ||
			           g_100b0c0[i].goods_id == 0x1c3) {
				g_100b0c0[i].flags |= 0x204;
				for (k = 0; k < g_100b0ac; k++) {
					if (g_100d0c0[k].goods_id == g_100b0c0[i].goods_id) {
						g_100d0c0[k].flags |= 0x204;
						break;
					}
				}
				if (k >= g_100b0ac) {
					g_100d0c0[g_100b0ac].goods_id = g_100b0c0[i].goods_id;
					for (j = 0; j < 4; j++) {
						g_100d0c0[g_100b0ac].building_indices[j] = -1;
					}
					g_100d0c0[g_100b0ac].min_1 = 0;
					g_100d0c0[g_100b0ac].min_2 = 0;
					g_100d0c0[g_100b0ac].value = -1.0e10f;
					g_100d0c0[g_100b0ac].amount = 0;
					g_100d0c0[g_100b0ac].unk_3c = 0;
					g_100d0c0[g_100b0ac].unk_40 = 0;
					g_100d0c0[g_100b0ac].unk_44 = 0;
					g_100d0c0[g_100b0ac].unk_48 = 0x21;
					g_100d0c0[g_100b0ac].flags = 0x204;
					g_100b0ac = g_100b0ac + 1;
				}
			}
		}
	}

	kind = ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) *(char**) (entity + 0x16c)].category;
	if (kind == 0x1d || kind == 0x1f) {
		for (i = 0; i < ai_ResourceCount; i++) {
			if (g_100b0c0[i].goods_id == 0x225 || g_100b0c0[i].goods_id == 0x226 || g_100b0c0[i].goods_id == 0x227 ||
			    g_100b0c0[i].goods_id == 0x293 || g_100b0c0[i].goods_id == 0x294 || g_100b0c0[i].goods_id == 0x295) {
				g_100b0c0[i].flags |= 0x404;
				for (k = 0; k < g_100b0ac; k++) {
					if (g_100d0c0[k].goods_id == g_100b0c0[i].goods_id) {
						g_100d0c0[k].flags |= 0x404;
						break;
					}
				}
				if (k >= g_100b0ac) {
					g_100d0c0[g_100b0ac].goods_id = g_100b0c0[i].goods_id;
					for (j = 0; j < 4; j++) {
						g_100d0c0[g_100b0ac].building_indices[j] = -1;
					}
					g_100d0c0[g_100b0ac].min_1 = 0;
					g_100d0c0[g_100b0ac].min_2 = 0;
					g_100d0c0[g_100b0ac].value = -1.0e10f;
					g_100d0c0[g_100b0ac].amount = 0;
					g_100d0c0[g_100b0ac].unk_3c = 0;
					g_100d0c0[g_100b0ac].unk_40 = 0;
					g_100d0c0[g_100b0ac].unk_44 = 0;
					g_100d0c0[g_100b0ac].unk_48 = 0x21;
					g_100d0c0[g_100b0ac].flags = 0x404;
					g_100b0ac = g_100b0ac + 1;
				}
			}
		}
	}

	for (i = 0; i < ai_ResourceCount; i++) {
		for (k = 0; k < g_100b0ac; k++) {
			if (g_100b0c0[i].goods_id == g_100d0c0[k].goods_id) {
				g_100b0c0[i].parent_index = k;
				break;
			}
		}
	}

	for (i = 0; i < g_100b0ac; i++) {
		goodsSlot = fcn_00502cd0(*(int*) (craft + 0x14), 1, 0, g_100d0c0[i].goods_id);
		if (goodsSlot == 0) {
			g_100d0c0[i].unk_3c = 0;
		} else {
			g_100d0c0[i].unk_3c = gm_GetMsgField(craft, goodsSlot);
		}
		g_100d0c0[i].unk_40 =
		    gm_eval_SlotVoll(craft, g_100d0c0[i].goods_id, 0xf4240);
	}

	for (i = 0; i < ai_ResourceCount; i++) {
		goodsSlot = fcn_00502cd0(*(int*) (craft + 0x14), 1, 0, g_100b0c0[i].goods_id);
		if (goodsSlot == 0) {
			g_100b0c0[i].stock = 0;
		} else {
			g_100b0c0[i].stock = gm_GetMsgField(craft, goodsSlot);
			if (g_100b0c0[i].stock == 0) {
				cm_RequestClearLagerslot(*(int*) (craft + 2), g_100b0c0[i].goods_id);
			}
		}
		g_100b0c0[i].capacity =
		    gm_eval_SlotVoll(craft, g_100b0c0[i].goods_id, 0xf4240);
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
			for (j = 0; j < g_100b0ac; j++) {
				if (id == g_100d0c0[j].goods_id) {
					g_100d0c0[j].amount += st.x68[i];
				}
			}
			for (j = 0; j < ai_ResourceCount; j++) {
				if (id == g_100b0c0[j].goods_id) {
					g_100b0c0[j].allocated += st.x68[i];
				}
			}
		}
		for (j = 0; j < 3; j++) {
			if (((unsigned short*) (action + 0xd6))[j] != 0) {
				for (i = 0; i < g_100b0ac; i++) {
					if (((unsigned short*) (action + 0xd6))[j] == g_100d0c0[i].goods_id) {
						g_100d0c0[i].amount += ((int*) (action + 0xdc))[j];
					}
				}
				for (i = 0; i < ai_ResourceCount; i++) {
					if (((unsigned short*) (action + 0xd6))[j] == g_100b0c0[i].goods_id) {
						g_100b0c0[i].allocated += ((int*) (action + 0xdc))[j];
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
				if (g_100b0c0[i].goods_id !=
				    (int) *(unsigned short*) (action + 0xae)) {
					continue;
				}
				g_100b0c0[i].allocated =
				    (int) (((float) gm_GetBuildingTechEffect(*(char**) (entity + 0x16c), 0xb, 1) * 0.01f + 1.0f) *
				               g_664124 +
				           (float) g_100b0c0[i].allocated);
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
				if (g_100b0c0[i].goods_id !=
				    (int) *(unsigned short*) (action + 0xae)) {
					continue;
				}
				g_100b0c0[i].allocated =
				    (int) (((float) gm_GetBuildingTechEffect(*(char**) (entity + 0x16c), 0xb, 1) * 0.01f + 1.0f) *
				               g_664124 +
				           (float) g_100b0c0[i].allocated);
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
				if (g_100b0c0[i].goods_id !=
				    (int) *(unsigned short*) (action + 0xac)) {
					continue;
				}
				g_100b0c0[i].allocated =
				    (int) (((float) gm_GetBuildingTechEffect(*(char**) (entity + 0x16c), 0xb, 1) * 0.01f + 1.0f) *
				               g_664124 +
				           (float) g_100b0c0[i].allocated);
			}
		}
	}

	for (i = 0; i < g_100b0ac; i++) {
		ai_CalcProductionGoodProfit(&g_100d0c0[i]);
	}

	for (i = 0; i < g_100b0ac; i++) {
		for (j = i; j < g_100b0ac; j++) {
			if (g_100d0c0[i].slope < g_100d0c0[j].slope) {
				tmp = g_100d0c0[i];
				g_100d0c0[i] = g_100d0c0[j];
				g_100d0c0[j] = tmp;
			}
		}
	}

	for (i = 0; i < ai_ResourceCount; i++) {
		if (g_100b0c0[i].parent_index != -1) {
			for (j = 0; j < g_100b0ac; j++) {
				if (g_100b0c0[i].goods_id == g_100d0c0[j].goods_id) {
					g_100b0c0[i].flags |= 0x40;
					g_100d0c0[j].flags |= 0x40;
					g_100b0c0[i].parent_index = j;
				}
			}
		}
	}

	for (i = 0; i < g_100b0ac; i++) {
		g_100d0c0[i].unk_48 = i;
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
