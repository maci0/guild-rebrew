#include <string.h>
#include "Develop/DieGildeAddOn/game/goods_plan.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
/* g_100d0c0: 0x58-byte object records.  The four dwords at +4 select the
 * building instances; +0x54 carries the state flags. */
#pragma pack(push, 1)
#include "production_goods.h"





















/* g_7f4ca0: 0x21c-byte map records. */
typedef struct Ent {
	unsigned short id;    /* 0x000 */
	unsigned char f2;     /* 0x002 */
	char pad3[5];
	unsigned char f8;     /* 0x008 */
	char pad9[0x15c];
	unsigned char f165;   /* 0x165 */
	char pad166[6];
	int f16c;             /* 0x16c */
	char pad170[0xc];
	char* host;           /* 0x17c */
	char pad180[4];
	int f184;             /* 0x184 */
	char pad188[0x94];
} Ent;

/* g_868050: 0x24d-byte level records. */
typedef struct Lvl {
	unsigned char kind;   /* 0x000 */
	char pad1[0x246];
	unsigned char level;  /* 0x247 */
	char pad248[5];
} Lvl;

/* lpObjektePROT: 0x41-byte item definitions. */
typedef struct ItemDef {
	unsigned char kind;   /* 0x00 */
	char pad1[0x25];
	unsigned short f26;   /* 0x26 */
	char pad28[0xe];
	unsigned short f36;   /* 0x36 */
	char pad38[9];
} ItemDef;

/* Scheduler state handed to fcn_00487f90. */
typedef struct Msg {
	int kind;             /* 0x00 */
	char* self;           /* 0x04 */
	char* rec;            /* 0x08 */
	char* p0c;            /* 0x0c */
	char* p10;            /* 0x10 */
	int want;             /* 0x14 */
	int avail;            /* 0x18 */
	int sent;             /* 0x1c */
	int total;            /* 0x20 */
} Msg;
#pragma pack(pop)

 
extern Ent gm_EntitySlotTable[];
extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;
extern char gm_EntityIdField[];
extern char gm_GameTime[];
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern int ai_ProductionGoodsCount;
extern int ai_ResourceCount;
extern int ai_MeisterDebugState;
extern int g_100dc34;

char* __cdecl gm_QueryEntities(int, int, int, ...);
char* __cdecl gm_NextEntityQueryMatch(void);
char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
char* __cdecl plt_FindPlantInfo(int);
void* __cdecl gm_FindCityItemHolder(int);
void __cdecl ai_CollectBuildingGoodsPlan(char*, char*, char*);
int __cdecl ai_CanProduceGood(char*, int*, int);
void __cdecl ai_PlanGoodIngredients(char*, int*);
void __cdecl ai_ManageMeisterWorkers(char*);
void __cdecl ai_BuyStallGoods(char*);
void __cdecl gm_TryAutoUpgradeBuildingSlots(char*, char*, int);
void __cdecl ai_RequestAusbauUpgrade(char*, char*, int);
void __cdecl ai_CancelBlockedActions(char*, int);
void __cdecl ai_DispatchMeisterAction(int*);
void __cdecl ai_MeisterCollectTrans(char*);
void __cdecl ai_MeisterTrade(char*, char*);
void __cdecl ai_RequestProductionGoods(char*);
void __cdecl cm_SendCopyEntityData(char*);
void __cdecl he_AssignActionSlot(char*, int, int, int);
void __cdecl cm_SendChainRecordLookup(int, int, int, int, int, int);
void* __cdecl gm_eval_SlotVoll(char*, int, int);
int __cdecl init_AllocateGebaeudeSceneSlot(char*);
int __cdecl hp_PickWeightedProdItem(int);
int __cdecl plt_CheckZoneAvailability(int, int, int, int);
int __cdecl gm_RandomMod(int);
/* ADDRESS: GOLDTL 0x0047f6b0 */
int __cdecl ai_RunResourceMaster(char* meister)
{
	Msg st;
	char* prod_slot;
	int* p2;
	int i;
	char* store_slot;
	int t;
	int flag;
	char* h;
	char* q;
	int j;
	int n;
	int v;
	char* craft_slot;

	prod_slot = gm_QueryEntities(*(int*) (*(char**) (meister + 0x16c) + 0x5d), 2, 6, 0, 0xff);
	if (prod_slot == 0) {
		return 0;
	}
	craft_slot = gm_QueryEntities(*(int*) (*(char**) (meister + 0x16c) + 0x5d), 2, 6, 0, 0x2a);
	if (craft_slot == 0) {
		return 0;
	}
	store_slot = gm_QueryEntities(*(int*) (*(char**) (meister + 0x16c) + 0x5d), 1, 0, 0xfe);
	if (store_slot == 0) {
		return 0;
	}
	ai_CollectBuildingGoodsPlan(meister, prod_slot, craft_slot);

	if (ai_ProductionGoodsCount > 0) {
		p2 = (int*) &ai_ProductionGoodsPlans[0].building_indices[0];
		for (n = ai_ProductionGoodsCount; n != 0; n--) {
			q = (char*) p2;
			for (i = 4; i != 0; i--) {
				if (*(int*) q >= 0 && ai_ResourceRequests[*(int*) q].parent_index >= 0) {
					ai_ProductionGoodsPlans[ai_ResourceRequests[*(int*) q].parent_index].flags |= 4;
					for (j = 0; j < ai_ResourceCount; j++) {
						if (ai_ProductionGoodsPlans[ai_ResourceRequests[*(int*) q].parent_index].goods_id
						    == ai_ResourceRequests[j].goods_id) {
							ai_ResourceRequests[j].flags |= 4;
						}
					}
				}
				q += 4;
			}
			p2 += 0x16;
		}
	}

	ai_ManageMeisterWorkers(meister);
	gm_TryAutoUpgradeBuildingSlots(craft_slot, meister, 0xa);
	ai_RequestAusbauUpgrade(craft_slot, meister, 0x19);
	ai_BuyStallGoods(meister);
	if ((*(unsigned char*) (meister + 0x1c8) & 0x10) == 0
	    && ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) (*(char**) (meister + 0x16c))].category != 0xb) {
		q = gm_QueryEntities(*(int*) (prod_slot + 0x14), 1, 4, 0x17);
		if (q != 0) {
			while (*(int*) (q + 0xe) != 1) {
				q = gm_NextEntityQueryMatch();
				if (q == 0) {
					*(int*) (meister + 0x1c8) |= 0x10;
					goto done_m;
				}
			}
			{
				char m[0xf8];
				memset(m, 0, sizeof(m));
				h = *(char**) (meister + 0x16c);
				m[4] = 9;
				*(int*) (m + 8) = *(int*) (gm_EntityIdField +
				                           *(unsigned short*) (h + 0x27) * 0x21c);
				*(int*) (m + 0xc) = *(int*) (h + 1);
				*(int*) (m + 0x10) = 0;
				*(int*) (m + 0x14) = 0;
				*(int*) (m + 0x28) = *(int*) &gm_GameTime;
				*(int*) (m + 0x2c) = gm_GameTimeHour;
				*(int*) (m + 0x30) = gm_GameTimeSliceDword;
				*(short*) (m + 0x34) = gm_GameTimeTailWord;
				m[0x36] = 1;
				*(int*) (m + 0x58) = *(int*) (h + 1);
				*(int*) (m + 0x5c) = *(int*) (prod_slot + 2);
				*(int*) (m + 0x60) = *(int*) (store_slot + 2);
				cm_SendCopyEntityData(m);
			}
		}
		*(int*) (meister + 0x1c8) |= 0x10;
done_m:
		;
	} else {
		q = prod_slot;
	}

	flag = 0;
	{
		char* s;
		s = he_StartHandlungSearch(2, 0, 9, 3, *(int*) (*(char**) (meister + 0x16c) + 1));
		if (s != 0) {
			if (*(int*) (meister + 0x17c) != (int) s) {
				he_AssignActionSlot(*(char**) (meister + 0x16c), 0, *(unsigned short*) meister, (int) s);
			}
			flag = 1;
		}
	}
	h = *(char**) (meister + 0x16c);
	if (gm_EntitySlotTable[*(unsigned short*) (h + 0x27)].f2 == 6) {
		v = hp_PickWeightedProdItem((int) h);
		if (q != 0) {
			for (i = 0; i < 0x20; i++) {
				if (ai_ProductionGoodsPlans[i].goods_id == v) {
					goto found;
				}
			}
		}
	}
	goto scan;

found:
	if ((int) *(unsigned char*) (craft_slot + 0x1c) < ai_ProductionGoodsPlans[i].min_1) {
		goto scan;
	}
	if ((int) *(unsigned char*) (craft_slot + 0x1d) < ai_ProductionGoodsPlans[i].min_2) {
		goto scan;
	}
	if (ai_ProductionGoodsPlans[i].unk_40 < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].value_036) {
		goto scan;
	}
	v = (int) gm_FindCityItemHolder(ai_ProductionGoodsPlans[i].goods_id);
	if (v == 0) {
		goto scan;
	}
	t = (int) gm_eval_SlotVoll((char*) v, ai_ProductionGoodsPlans[i].goods_id, 0xf4240);
	if (t < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].value_036 + ai_ProductionGoodsPlans[i].unk_3c) {
		goto scan;
	}
	if (((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].kind == 0x17) {
		q = gm_QueryEntities(*(int*) (store_slot + 0x14), 1, 0, ai_ProductionGoodsPlans[i].goods_id);
		if (q == 0) {
			goto scan;
		}
		if (*(int*) (q + 0xe) < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].value_036) {
			goto scan;
		}
		ai_ProductionGoodsPlans[i].flags |= 8;
		ai_PlanGoodIngredients(meister, (int*) &ai_ProductionGoodsPlans[i]);
	} else if (ai_CanProduceGood(meister, (int*) &ai_ProductionGoodsPlans[i], 1)) {
		ai_ProductionGoodsPlans[i].flags |= 8;
		ai_PlanGoodIngredients(meister, (int*) &ai_ProductionGoodsPlans[i]);
	} else if (ai_CanProduceGood(meister, (int*) &ai_ProductionGoodsPlans[i], 0)) {
		ai_PlanGoodIngredients(meister, (int*) &ai_ProductionGoodsPlans[i]);
	} else {
		goto scan;
	}
	goto after;

scan:
	for (i = 0; i < ai_ProductionGoodsCount; i++) {
		if (ai_ProductionGoodsPlans[i].flags & 4) {
			continue;
		}
		if ((int) *(unsigned char*) (craft_slot + 0x1c) < ai_ProductionGoodsPlans[i].min_1) {
			continue;
		}
		if ((int) *(unsigned char*) (craft_slot + 0x1d) < ai_ProductionGoodsPlans[i].min_2) {
			continue;
		}
		if (ai_ProductionGoodsPlans[i].unk_40 < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].value_036) {
			continue;
		}
		v = (int) gm_FindCityItemHolder(ai_ProductionGoodsPlans[i].goods_id);
		if (v == 0) {
			continue;
		}
		t = (int) gm_eval_SlotVoll((char*) v, ai_ProductionGoodsPlans[i].goods_id, 0xf4240);
		if (t < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].value_036 + ai_ProductionGoodsPlans[i].unk_3c) {
			continue;
		}
		if (((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].kind == 0x17) {
			q = gm_QueryEntities(*(int*) (store_slot + 0x14), 1, 0, ai_ProductionGoodsPlans[i].goods_id);
			if (q == 0) {
				continue;
			}
			if (*(int*) (q + 0xe) < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].value_036) {
				continue;
			}
			ai_ProductionGoodsPlans[i].flags |= 8;
			ai_PlanGoodIngredients(meister, (int*) &ai_ProductionGoodsPlans[i]);
			goto after;
		} else if (ai_CanProduceGood(meister, (int*) &ai_ProductionGoodsPlans[i], 1)) {
			ai_ProductionGoodsPlans[i].flags |= 8;
			ai_PlanGoodIngredients(meister, (int*) &ai_ProductionGoodsPlans[i]);
			goto after;
		}
	}

after:
	for (i = 0; i < ai_ProductionGoodsCount; i++) {
		if (ai_ProductionGoodsPlans[i].flags & 8) {
			break;
		}
		if (ai_ProductionGoodsPlans[i].flags & 4) {
			continue;
		}
		if ((int) *(unsigned char*) (craft_slot + 0x1c) < ai_ProductionGoodsPlans[i].min_1) {
			continue;
		}
		if ((int) *(unsigned char*) (craft_slot + 0x1d) < ai_ProductionGoodsPlans[i].min_2) {
			continue;
		}
		if (ai_ProductionGoodsPlans[i].unk_40 < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].value_036) {
			continue;
		}
		v = (int) gm_FindCityItemHolder(ai_ProductionGoodsPlans[i].goods_id);
		if (v == 0) {
			continue;
		}
		t = (int) gm_eval_SlotVoll((char*) v, ai_ProductionGoodsPlans[i].goods_id, 0xf4240);
		if (t < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].value_036 + ai_ProductionGoodsPlans[i].unk_3c) {
			continue;
		}
		if (((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].kind == 0x17) {
			ai_ProductionGoodsPlans[i].flags |= 0x10;
			break;
		}
		if (ai_CanProduceGood(meister, (int*) &ai_ProductionGoodsPlans[i], 0)) {
			ai_PlanGoodIngredients(meister, (int*) &ai_ProductionGoodsPlans[i]);
			break;
		}
	}

	for (i = 0; i < ai_ProductionGoodsCount; i++) {
		if ((ai_ProductionGoodsPlans[i].flags & 8) == 0) {
			continue;
		}
		if (((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].kind == 0x17) {
			if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) (*(char**) (meister + 0x16c))].category == 0xb) {
				ai_ProductionGoodsPlans[i].flags |= 0x10;
			} else {
				q = gm_QueryEntities(*(int*) (store_slot + 0x14), 1, 0, ai_ProductionGoodsPlans[i].goods_id);
				if (q == 0
				    || *(int*) (q + 0xe) < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].value_036) {
					ai_ProductionGoodsPlans[i].flags =
					    (ai_ProductionGoodsPlans[i].flags & ~8) | 0x10;
				}
			}
		} else {
			for (j = 0; j != 4; j++) {
				if (ai_ResourceRequests[ai_ProductionGoodsPlans[i].building_indices[j]].stock
				    < (int) ((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[i].goods_id].ingredient_amounts[0]) {
					ai_ProductionGoodsPlans[i].flags &= ~8;
				}
			}
		}
	}

	ai_CancelBlockedActions(meister, 4);
	ai_CancelBlockedActions(meister, 8);
	ai_CancelBlockedActions(meister, 3);

	st.avail = 0;
	for (j = 0; j < 0x300; j++) {
		if (gm_EntitySlotTable[j].f8 > 0 && gm_EntitySlotTable[j].id != 0xffff
		    && gm_EntitySlotTable[j].f2 != 0xa
		    && gm_EntitySlotTable[j].f16c == *(int*) (meister + 0x16c)
		    && gm_EntitySlotTable[j].f165 != 0
		    && gm_EntitySlotTable[j].f184 != 0
		    && *(int*) (gm_EntitySlotTable[j].f184 + 0x2c) == *(int*) (*(char**) (meister + 0x16c) + 1)
		    && (gm_EntitySlotTable[j].host == 0 || *(unsigned char*) gm_EntitySlotTable[j].host != 0x28)
		    && !(flag != 0 && (char*) meister == (char*) &gm_EntitySlotTable[j])) {
			he_AssignActionSlot(*(char**) (meister + 0x16c), 0, gm_EntitySlotTable[j].id, 0);
			st.avail++;
		}
	}
	if (ai_MeisterDebugState == *(int*) (meister + 0x16c)) {
		g_100dc34 = st.avail;
	}
	st.want = 0;
	{
		int* f;

		f = &ai_ProductionGoodsPlans[0].flags;
		for (i = 0; i < ai_ProductionGoodsCount; i++) {
			if (*f & 8) {
				st.want++;
			}
			if (*f & 0x10) {
				if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) (*(char**) (meister + 0x16c))].category != 0xb) {
					st.want++;
				}
			}
			f = (int*) ((char*) f + 0x58);
		}
	}
	if (st.want >= st.avail) {
		st.want = st.avail;
	}
	if (st.avail == 0 || st.want == 0) {
		ai_MeisterCollectTrans(meister);
		ai_MeisterTrade(meister, craft_slot);
		return 0;
	}

	st.p0c = craft_slot;
	st.p10 = store_slot;
	st.self = meister;
	st.total = 0;
	st.sent = 0;
	if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) (*(char**) (meister + 0x16c))].category != 0xb) {
		goto ltail;
	}
	if ((unsigned short) gm_GameTimeHour % 2 == 0) {
		*(int*) (meister + 0x1b4) &= ~0x20;
		goto ltail;
	}
	if ((*(int*) (meister + 0x1b4) & 0x20) != 0) {
		goto ltail;
	}
	v = init_AllocateGebaeudeSceneSlot(*(char**) (meister + 0x16c));
	p2 = *(char**) (0x104336c + v * 0x3dc);
	if (p2 == 0) {
		return 0;
	}
	n = *(int*) (*(char**) (meister + 0x16c) + 0x71);
	{
		int ch;
		char* g;

		ch = -1;
		for (i = 0; i < 8; i++) {
			if (strstr((char*) p2 + 0x7e24 + i * 0x40, (char*) 0x67dd10) != 0) {
				ch = i;
			}
		}
		for (i = 0; i < ai_ProductionGoodsCount * 4; i++) {
			j = gm_RandomMod(ai_ProductionGoodsCount) & 0xffff;
			if (((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[j].goods_id].kind == 0x17) {
				break;
			}
		}
		if (((OBJECT_PROTOTYPE*) lpObjektePROT)[ai_ProductionGoodsPlans[j].goods_id].kind != 0x17) {
			goto lflag;
		}
		g = plt_FindPlantInfo(ai_ProductionGoodsPlans[j].goods_id);
		v = 0;
		for (i = 0; i < *(int*) p2 && v < 4; i++) {
			for (j = 0; v < 4 && j < *(int*) p2; j++) {
				if ((int) *(unsigned char*) (*(int*) ((char*) p2 + 0x14)
				                             + i * *(int*) p2 + j) != ch) {
					continue;
				}
				if (plt_CheckZoneAvailability(n, j, i, *(unsigned char*) (g + 0x42)) == 0) {
					continue;
				}
				cm_SendChainRecordLookup(*(int*) (*(char**) (meister + 0x16c) + 1), j, i, *(unsigned short*) g, 0, -1);
				v++;
			}
		}
	}
lflag:
	*(int*) (meister + 0x1b4) |= 0x20;

ltail:
	{
		char* rec;

		rec = (char*) &ai_ProductionGoodsPlans[0];
		for (i = 0; i < ai_ProductionGoodsCount; i++) {
			if (((PRODUCTION_GOODS_RECORD*) rec)->flags & 0x10) {
				if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) (*(char**)(meister + 0x16c))].category != 0xb) {
					st.kind = 8;
					st.rec = rec;
					ai_DispatchMeisterAction((int*) &st);
				}
			}
			if (((PRODUCTION_GOODS_RECORD*) rec)->flags & 8) {
					if (((OBJECT_PROTOTYPE*) lpObjektePROT)[((PRODUCTION_GOODS_RECORD*) rec)->goods_id].kind == 0x17) {
						st.rec = rec;
						if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*(unsigned char*) (*(char**)(meister + 0x16c))].category == 0xb) {
							st.kind = 0x28;
							ai_DispatchMeisterAction((int*) &st);
							if (ai_MeisterDebugState == *(int*)(meister + 0x16c) && *(int*) 0x100dc3c < 4) {
								*(PRODUCTION_GOODS_RECORD*) (0x100ddc0 + *(int*) 0x100dc3c * 0x58) =
								    *(PRODUCTION_GOODS_RECORD*) st.rec;
								*(int*) 0x100dc3c = *(int*) 0x100dc3c + 1;
							}
							goto next_rec;
						} else {
							st.kind = 3;
						}
					} else {
						st.kind = 4;
						st.rec = rec;
					}
					ai_DispatchMeisterAction((int*) &st);
					if (ai_MeisterDebugState == *(int*)(meister + 0x16c) && *(int*) 0x100dc3c < 4) {
						*(PRODUCTION_GOODS_RECORD*) (0x100ddc0 + *(int*) 0x100dc3c * 0x58) =
						    *(PRODUCTION_GOODS_RECORD*) st.rec;
						*(int*) 0x100dc3c = *(int*) 0x100dc3c + 1;
					}
				}
next_rec:
			rec += 0x58;
		}
	}

	ai_RequestProductionGoods(craft_slot);
	ai_MeisterCollectTrans(meister);
	ai_MeisterTrade(meister, craft_slot);
	return 0;
}
