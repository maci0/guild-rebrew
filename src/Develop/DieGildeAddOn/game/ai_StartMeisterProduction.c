/*
 * AI master variant of the production start: probes both crafting slots,
 * tries the current goods record, then walks the building table in random
 * order looking for a producer that can start.
 */
#include <string.h>
#include "Develop/DieGildeAddOn/game/goods_plan.h"
#include <stdio.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
typedef struct {
	char pad0[0x16c];
	int x16c;          /* +0x16c: shared building state */
	char pad170[0x1b4 - 0x170];
	int f1b4;          /* +0x1b4: selection flags */
	int pad1b8;
	unsigned short id; /* +0x1bc: current goods record id */
} Bld;
#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/production_goods.h"












typedef struct {
	char pad0[0x1c];
	unsigned char x1c;
	unsigned char x1d;
} Craft;

typedef struct {
	int kind;          /* +0x00: request kind */
	int bld;           /* +0x04: owning building */
	int rec;           /* +0x08: building record */
	int craft;         /* +0x0c: crafting slot */
	int x10;           /* +0x10 */
	int flags;         /* +0x14: flagged record count */
	int count;         /* +0x18: scanned record count */
	int x1c;           /* +0x1c */
	int x20;           /* +0x20 */
} Req; /* 0x24 */

extern char* lpObjektePROT;  /* +0x41 stride goods records: type byte, name */
 
extern int ai_ResourceCount;        /* ware count */
extern int ai_ProductionGoodsCount;        /* building count */
extern int ai_MeisterDebugState;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100dc3c;
extern char ai_TrackedGoodPlanCounts[];
extern char g_100dc60[];
extern char g_100ddc0[];
extern char ai_TrackedGoodPlanEntries[];
extern unsigned short gm_GameTimeHour;
extern char gm_EntitySlotTable[];

int __cdecl gm_QueryEntities(int, int, int, int, int);
void __cdecl ai_CollectBuildingGoodsPlan(Bld*, int, int);
void __cdecl ai_ManageMeisterWorkers(Bld*);
void __cdecl gm_TryAutoUpgradeBuildingSlots(int, Bld*, int);
void __cdecl ai_RequestAusbauUpgrade(int, Bld*, int);
void __cdecl ai_BuyStallGoods(Bld*);
int __cdecl ai_CanProduceGood(Bld*, PRODUCTION_GOODS_RECORD*, int);
void __cdecl ai_PlanGoodIngredients(Bld*, PRODUCTION_GOODS_RECORD*);
int __cdecl hp_PickWeightedProdItem(int);
int __cdecl gm_FindCityItemHolder(int);
int __cdecl gm_eval_SlotVoll(int, int, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl ai_RequestProductionGoods(int);
void __cdecl ai_PlanResourceRestock(Bld*, int);
void __cdecl he_AssignActionSlot(int, int, int, int);
void __cdecl ai_CancelBlockedActions(Bld*, int);
void __cdecl ai_DispatchMeisterAction(Req*);
void __cdecl fcn_00489250(Bld*);
void __cdecl fcn_00489a70(Bld*, int);

/* Starts the production of the current goods if any producer in the building
 * table can run it in the current town. */
/* ADDRESS: GOLDTL 0x0047ebc0 */
void __cdecl ai_StartMeisterProduction(Bld* bld)
{
	char name[0x100];
	int order[0x20];
	Req put;
	int craft;
	int i;

	int prod;
	int hit;
	int j;
	int r;
	int n;
	int val;
	PRODUCTION_GOODS_RECORD* rec;

	hit = 0;
	prod = gm_QueryEntities(*(int*) (bld->x16c + 0x5d), 2, 6, 0, 0xff);
	if (prod == 0)
		return;
	craft = gm_QueryEntities(*(int*) (bld->x16c + 0x5d), 2, 6, 0, 0x2a);
	if (craft == 0)
		return;
	ai_CollectBuildingGoodsPlan(bld, prod, craft);
	ai_ManageMeisterWorkers(bld);
	gm_TryAutoUpgradeBuildingSlots(craft, bld, 0x4b);
	ai_RequestAusbauUpgrade(craft, bld, 0x19);
	ai_BuyStallGoods(bld);
	if (gm_GameTimeHour != 0xd && gm_GameTimeHour != 8) {
		for (i = 0; i < ai_ProductionGoodsCount; i++) {
			rec = (PRODUCTION_GOODS_RECORD*) ((char*) ai_ProductionGoodsPlans + i * 0x58);
			if (rec->goods_id != (int) bld->id)
				continue;
			if ((int) *(unsigned short*) ((((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 0x36) <= rec->unk_40 &&
			    ai_CanProduceGood(bld, rec, 1)) {
				rec->flags = rec->flags | 8;
				ai_PlanGoodIngredients(bld, rec);
				bld->id = (unsigned short) rec->goods_id;
				hit = 1;
			}
			break;
		}
		bld->f1b4 = bld->f1b4 & 0xfffffeff;
		if (hit)
			goto done;
	}
	else if (bld->f1b4 & 0x100) {
		if (bld->id != 0) {
			for (i = 0; i < ai_ProductionGoodsCount; i++) {
				rec = (PRODUCTION_GOODS_RECORD*) ((char*) ai_ProductionGoodsPlans + i * 0x58);
				if (rec->goods_id != (int) bld->id)
					continue;
				if ((int) *(unsigned short*) ((((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 0x36) <= rec->unk_40 &&
				    ai_CanProduceGood(bld, rec, 1)) {
					rec->flags = rec->flags | 8;
					ai_PlanGoodIngredients(bld, rec);
					bld->id = (unsigned short) rec->goods_id;
					goto done;
				}
				break;
			}
		}
	}
	else {
		bld->id = 0;
		bld->f1b4 = bld->f1b4 | 0x100;
	}
	if (*(unsigned char*) ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (bld->x16c + 0x27)].entity_state) == 6) {
		n = hp_PickWeightedProdItem(bld->x16c);
		if (n != 0) {
			for (rec = (PRODUCTION_GOODS_RECORD*) ai_ProductionGoodsPlans; (char*) rec < (char*) ai_ProductionGoodsPlans + 0xb00; rec = (PRODUCTION_GOODS_RECORD*) ((char*) rec + 0x58)) {
				if (rec->goods_id != n)
					continue;
				if ((int) ((Craft*) craft)->x1c < rec->min_1)
					break;
				if ((int) ((Craft*) craft)->x1d < rec->min_2)
					break;
				if (rec->unk_40 < (int) *(unsigned short*) ((((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 0x36))
					break;
				val = gm_FindCityItemHolder(rec->goods_id);
				if (val == 0)
					break;
				if ((int) ((unsigned short) *(unsigned short*) ((((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 0x36) + rec->unk_3c) <= gm_eval_SlotVoll(val, rec->goods_id, 1000000)) {
					if (ai_CanProduceGood(bld, rec, 1)) {
						rec->flags = rec->flags | 8;
						ai_PlanGoodIngredients(bld, rec);
						bld->id = (unsigned short) rec->goods_id;
						sprintf(name, "Produktion von %s starten, da Humanplayer es so will.", (((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 1);
						goto done;
					}
					if (ai_CanProduceGood(bld, rec, 0)) {
						ai_PlanGoodIngredients(bld, rec);
						bld->id = (unsigned short) rec->goods_id;
						sprintf(name, "Produktion von %s starten obwohl Rohstoffe fehlen, da der spieler es so will", (((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 1);
						goto done;
					}
				}
				break;
			}
		}
	}
	for (i = 0; i < 0x20; i++)
		order[i] = i;
	for (i = 0; i < 0x20; i++) {
		r = gm_RandomMod(0x20) & 0xffff;
		val = order[i];
		order[i] = order[r];
		order[r] = val;
	}
	for (i = 0; i < ai_ProductionGoodsCount; i++) {
		rec = (PRODUCTION_GOODS_RECORD*) ((char*) ai_ProductionGoodsPlans + order[i] * 0x58);
		if ((rec->flags & 0x20) || (rec->flags & 0x200))
			continue;
		if ((((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id].kind == 0x17 || ((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id].kind == 0x25) && rec->unk_3c >= 5)
			continue;
		if ((int) ((Craft*) craft)->x1c < rec->min_1)
			continue;
		if ((int) ((Craft*) craft)->x1d < rec->min_2)
			continue;
		if (rec->unk_40 < (int) *(unsigned short*) ((((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 0x36))
			continue;
		n = gm_FindCityItemHolder(rec->goods_id);
		if (n == 0)
			continue;
		if ((int) ((unsigned short) *(unsigned short*) ((((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 0x36) + rec->unk_3c) > gm_eval_SlotVoll(n, rec->goods_id, 1000000))
			continue;
		if (!ai_CanProduceGood(bld, rec, 1))
			continue;
		rec->flags = rec->flags | 8;
		ai_PlanGoodIngredients(bld, rec);
		bld->id = (unsigned short) rec->goods_id;
		sprintf(name, "Produktion von %s starten", (((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 1);
		goto done;
	}
	for (i = 0; i < ai_ProductionGoodsCount; i++) {
		rec = (PRODUCTION_GOODS_RECORD*) ((char*) ai_ProductionGoodsPlans + order[i] * 0x58);
		if ((rec->flags & 0x20) || (rec->flags & 0x200))
			continue;
		if ((((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id].kind == 0x17 || ((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id].kind == 0x25) && rec->unk_3c >= 5)
			continue;
		if ((int) ((Craft*) craft)->x1c < rec->min_1)
			continue;
		if ((int) ((Craft*) craft)->x1d < rec->min_2)
			continue;
		if (rec->unk_40 < (int) *(unsigned short*) ((((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 0x36))
			continue;
		n = gm_FindCityItemHolder(rec->goods_id);
		if (n == 0)
			continue;
		if ((int) ((unsigned short) *(unsigned short*) ((((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 0x36) + rec->unk_3c) > gm_eval_SlotVoll(n, rec->goods_id, 1000000))
			continue;
		if (!ai_CanProduceGood(bld, rec, 0))
			continue;
		ai_PlanGoodIngredients(bld, rec);
		bld->id = (unsigned short) rec->goods_id;
		sprintf(name, "Produktion von %s starten obwohl Rohstoffe fehlen", (((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 1);
		goto done;
	}
	bld->id = 0;
done:
	ai_RequestProductionGoods(craft);
	ai_PlanResourceRestock(bld, craft);
	if (0 < ai_ProductionGoodsCount) {
		for (i = 0; i < ai_ProductionGoodsCount; i++) {
			rec = (PRODUCTION_GOODS_RECORD*) ((char*) ai_ProductionGoodsPlans + i * 0x58);
			if (rec->flags & 8) {
				for (j = 0; j < 4; j++) {
					if (ai_ResourceRequests[rec->building_indices[j]].stock < (int) *(unsigned short*) ((((char*)&((OBJECT_PROTOTYPE*)lpObjektePROT)[rec->goods_id])) + 0x26 + j * 2))
						rec->flags = rec->flags & 0xfffffff7;
				}
			}
		}
	}
	if (ai_ProductionGoodsCount > 0) {
		for (i = 0; i < ai_ProductionGoodsCount; i++) {
			rec = (PRODUCTION_GOODS_RECORD*) ((char*) ai_ProductionGoodsPlans + i * 0x58);
			val = rec->flags;
			if ((val & 0x20) || (val & 0x200))
				rec->flags = val & 0xfffffff7;
		}
	}
	if (ai_ResourceCount > 0) {
		for (i = 0; i < ai_ResourceCount; i++) {
			val = ai_ResourceRequests[i].flags;
			if (((val & 0x20) || (val & 0x200)) && (val & 0x10) &&
			    ai_ResourceRequests[i].parent_index >= 0) {
				rec = (PRODUCTION_GOODS_RECORD*) ((char*) ai_ProductionGoodsPlans + ai_ResourceRequests[i].parent_index * 0x58);
				rec->flags = rec->flags | 0x10;
			}
		}
	}
	if (ai_MeisterDebugState == bld->x16c && g_100dc38 < 4) {
		i = 0;
		while (i < ai_ProductionGoodsCount && g_100dc38 < 4) {
			rec = (PRODUCTION_GOODS_RECORD*) ((char*) ai_ProductionGoodsPlans + i * 0x58);
			memcpy(g_100dc60 + g_100dc38 * 0x58, rec, 0x58);
			for (j = 0; j < 4; j++) {
				if (rec->building_indices[j] >= 0) {
					n = *(int*) (ai_TrackedGoodPlanCounts + g_100dc38 * 4);
					memcpy(ai_TrackedGoodPlanEntries + (n + g_100dc38 * 4) * 0x40, &ai_ResourceRequests[rec->building_indices[j]], 0x40);
					*(int*) (ai_TrackedGoodPlanCounts + g_100dc38 * 4) = *(int*) (ai_TrackedGoodPlanCounts + g_100dc38 * 4) + 1;
				}
			}
			g_100dc38 = g_100dc38 + 1;
			i = i + 1;
		}
	}
	ai_CancelBlockedActions(bld, 4);
	put.count = 0;
	for (n = 0x7f4ca2; n < 0x85a0a2; n += 0x21c) {
		if (*(unsigned char*) (n + 6) <= 0)
			continue;
		if (*(short*) (n - 2) == -1)
			continue;
		if (*(unsigned char*) n == 0xa)
			continue;
		if (*(int*) (n + 0x16a) != bld->x16c)
			continue;
		if (*(unsigned char*) (n + 0x163) == 0)
			continue;
		if (*(int*) (n + 0x182) == 0)
			continue;
		if (*(int*) (*(int*) (n + 0x182) + 0x2c) != *(int*) (*(int*) (n + 0x16a) + 1))
			continue;
		if (*(int*) (n + 0x17a) != 0) {
			if (*(unsigned char*) (*(int*) (n + 0x17a)) == 0x14)
				continue;
			if (*(unsigned char*) (*(int*) (n + 0x17a)) == 0x15)
				continue;
		}
		he_AssignActionSlot(bld->x16c, 0, (int) *(unsigned short*) (n - 2), 0);
		put.count = put.count + 1;
	}
	if (ai_MeisterDebugState == bld->x16c)
		g_100dc34 = put.count;
	put.flags = 0;
	if (ai_ProductionGoodsCount > 0) {
		for (i = 0; i < ai_ProductionGoodsCount; i++) {
			rec = (PRODUCTION_GOODS_RECORD*) ((char*) ai_ProductionGoodsPlans + i * 0x58);
			if (rec->flags & 8)
				put.flags = put.flags + 1;
			if (rec->flags & 0x10)
				put.flags = put.flags + 1;
		}
	}
	if (put.flags >= put.count)
		put.flags = put.count;
	if (put.count == 0 || put.flags == 0) {
		fcn_00489250(bld);
		fcn_00489a70(bld, craft);
		return;
	}
	if (ai_ProductionGoodsCount > 0) {
		put.bld = (int) bld;
		put.craft = craft;
		put.x10 = 0;
		put.x20 = 0;
		put.x1c = 0;
		i = 0;
		for (; i < ai_ProductionGoodsCount; i++) {
			val = *(int*) ((char*) ai_ProductionGoodsPlans + i * 0x58 + 0x54);
			if (val & 0x10) {
				if (val & 0x20) {
					put.kind = 0x14;
					put.rec = (int) ((char*) ai_ProductionGoodsPlans + i * 0x58);
					ai_DispatchMeisterAction(&put);
				}
				else if (val & 0x200) {
					put.kind = 0x15;
					put.rec = (int) ((char*) ai_ProductionGoodsPlans + i * 0x58);
					ai_DispatchMeisterAction(&put);
				}
				else
					continue;
			}
			else if (val & 8) {
				put.kind = 4;
				put.rec = (int) ((char*) ai_ProductionGoodsPlans + i * 0x58);
				ai_DispatchMeisterAction(&put);
			}
			else
				continue;
			if (ai_MeisterDebugState == bld->x16c && g_100dc3c < 4) {
				memcpy(g_100ddc0 + g_100dc3c * 0x58, (void*) put.rec, 0x58);
				g_100dc3c = g_100dc3c + 1;
			}
		}
	}
	fcn_00489250(bld);
	fcn_00489a70(bld, craft);
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_930600[452112];
#endif
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_90e0a0[592752];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_99e0a4[2924];
#endif
