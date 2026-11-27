#include <string.h>
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#pragma intrinsic(memcpy)

/* Entity record handed to the production planner (fields used here only). */
typedef struct {
	char pad0[0x16c];
	int root;			/* +0x16c, production building object */
	char pad170[0x44];
	int flags;			/* +0x1b4 */
	char pad1b8[4];
	unsigned short item;		/* +0x1bc */
} AI_MASTER_ENTITY;

/* SIZE 0x58, production entry */
#include "production_goods.h"











/* SIZE 0x40, resource entry */
typedef struct {
	int id;				/* +0x00 */
	char pad04[0x34];
	int flags;			/* +0x38 */
} Res483f20;

/* Start request handed to fcn_00487f90. */
typedef struct {
	int kind;			/* +0x00 */
	int ent;			/* +0x04 */
	int entry;			/* +0x08 */
} AI_MEISTER_PLAN;

extern char* lpObjektePROT;			/* entity type table, entry stride 0x41 */
#include "Develop/DieGildeAddOn/game/entity_record.h"
 
extern int g_100b0ac;			/* production entry count */
extern char g_100b0c4[];		/* resource entry table, stride 0x40 */
extern int ai_ResourceCount;			/* resource entry count */
extern char g_100b0e8[];
extern int g_100dc20;			/* owner production building */
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100dc3c;
extern int g_100dc40[];
extern int* g_100dc48;
extern unsigned short g_7f4c04;

void* __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl ai_CollectBuildingGoodsPlan(AI_MASTER_ENTITY*, void*, void*);
void __cdecl ai_ManageMeisterWorkers(AI_MASTER_ENTITY*);
void __cdecl gm_TryAutoUpgradeBuildingSlots(void*, AI_MASTER_ENTITY*, int);
void __cdecl ai_RequestAusbauUpgrade(void*, AI_MASTER_ENTITY*, int);
void __cdecl ai_BuyStallGoods(AI_MASTER_ENTITY*);
int __cdecl ai_CanProduceGood(AI_MASTER_ENTITY*, PRODUCTION_GOODS_RECORD*, int);
void __cdecl ai_PlanGoodIngredients(AI_MASTER_ENTITY*, PRODUCTION_GOODS_RECORD*);
int __cdecl hp_PickWeightedProdItem(int);
void* __cdecl gm_FindCityItemHolder(int);
int __cdecl gm_eval_SlotVoll(void*, int, int);
int __cdecl gm_RandomMod(int);
void __cdecl ai_RequestProductionGoods(void*);
void __cdecl ai_PlanResourceRestock(AI_MASTER_ENTITY*, void*);
void __cdecl ai_CancelBlockedActions(AI_MASTER_ENTITY*, int);
void __cdecl he_AssignActionSlot(int, int, unsigned short, int);
void __cdecl ai_MeisterCollectTrans(AI_MASTER_ENTITY*);
void __cdecl ai_MeisterTrade(AI_MASTER_ENTITY*, void*);
void __cdecl ai_DispatchMeisterAction(AI_MEISTER_PLAN*);
int __cdecl wsprintfA(char*, char*, ...);

#define type_entry(id) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[(id)]))
#define slot_at(id) ((char*)&((ENTITY_RECORD*)g_7f4ca0)[(id)])

/* Runs the start preconditions and returns fcn_00486640's answer. */
static __inline int can_start(AI_MASTER_ENTITY* e, void* rec, PRODUCTION_GOODS_RECORD* p, int human)
{
	char* type;
	void* obj;
	int amount;

	if ((p->flags & 0x400) != 0) {
		return 0;
	}
	type = type_entry(p->goods_id);
	if ((*type == 0x17 || *type == 0x25) && p->unk_3c >= 5) {
		return 0;
	}
	if (*(unsigned char*) ((char*) rec + 0x1c) < p->min_1) {
		return 0;
	}
	if (*(unsigned char*) ((char*) rec + 0x1d) < p->min_2) {
		return 0;
	}
	if (((OBJECT_PROTOTYPE *)type)->value_036 > p->unk_40) {
		return 0;
	}
	obj = gm_FindCityItemHolder(p->goods_id);
	if (obj == 0) {
		return 0;
	}
	amount = gm_eval_SlotVoll(obj, p->goods_id, 1000000);
	if (amount < ((OBJECT_PROTOTYPE *)type_entry(p->goods_id))->value_036 + p->unk_3c) {
		return 0;
	}
	return ai_CanProduceGood(e, p, human);
}

static __inline void start_production(AI_MASTER_ENTITY* e, PRODUCTION_GOODS_RECORD* p, char* fmt, char* msg)
{
	p->flags |= 8;
	ai_PlanGoodIngredients(e, p);
	e->item = (unsigned short) p->goods_id;
	if (fmt != 0) {
		wsprintfA(msg, fmt, type_entry(p->goods_id) + 1);
	}
}

/* ADDRESS: GOLDTL 0x00483f20 */
void __cdecl ai_RunWorkshopMaster(AI_MASTER_ENTITY* e)
{
	PRODUCTION_GOODS_RECORD* prod;
	PRODUCTION_GOODS_RECORD* scan;
	Res483f20* res;
	AI_MEISTER_PLAN plan;
	char* slot;
	char* type;
	char* p;
	void* rec;
	void* stk;
	int order[0x20];
	char msg[0x100];
	int built;
	int found;
	int i;
	int k;
	int r;
	int t;
	int n;
	int id;

	rec = fcn_00502cd0(*(int*) ((char*) e->root + 0x5d), 2, 6, 0, 0xff);
	if (rec == 0) {
		return;
	}
	stk = fcn_00502cd0(*(int*) ((char*) e->root + 0x5d), 2, 6, 0, 0x2a);
	if (stk == 0) {
		return;
	}
	ai_CollectBuildingGoodsPlan(e, rec, stk);
	ai_ManageMeisterWorkers(e);
	gm_TryAutoUpgradeBuildingSlots(stk, e, 0x4b);
	ai_RequestAusbauUpgrade(stk, e, 0x19);
	ai_BuyStallGoods(e);

	if (g_7f4c04 == 8 || g_7f4c04 == 0xd) {
		if ((e->flags & 0x100) == 0) {
			e->item = 0;
			e->flags |= 0x100;
		} else if (e->item != 0) {
			for (i = 0; i < g_100b0ac; i++) {
				if (g_100d0c0[i].goods_id != e->item) {
					continue;
				}
				if (g_100d0c0[i].unk_40 >= ((OBJECT_PROTOTYPE *)type_entry(g_100d0c0[i].goods_id))->value_036 &&
				    ai_CanProduceGood(e, &g_100d0c0[i], 1) != 0) {
					start_production(e, &g_100d0c0[i], 0, msg);
					goto after_start;
				}
				break;
			}
		}
	} else {
		found = 0;
		for (i = 0; i < g_100b0ac; i++) {
			if (g_100d0c0[i].goods_id != e->item) {
				continue;
			}
			if (g_100d0c0[i].unk_40 >= ((OBJECT_PROTOTYPE *)type_entry(g_100d0c0[i].goods_id))->value_036 &&
			    ai_CanProduceGood(e, &g_100d0c0[i], 1) != 0) {
				start_production(e, &g_100d0c0[i], 0, msg);
				found = 1;
			}
			break;
		}
		e->flags &= ~0x100;
		if (found) {
			goto after_start;
		}
	}

	slot = slot_at(*(unsigned short*) ((char*) e->root + 0x27));
	if (*(char*) (slot + 2) == 6 &&
	    (id = hp_PickWeightedProdItem(e->root)) != 0) {
		for (scan = g_100d0c0, i = 0; (char*) scan < (char*) 0x100dbc0; scan = (PRODUCTION_GOODS_RECORD*) ((char*) scan + 0x58), i++) {
			if (scan->goods_id == id) {
				if (can_start(e, stk, scan, 1)) {
					start_production(e, scan, (char*) 0x67dcc0, msg);
					goto after_start;
				}
				if (ai_CanProduceGood(e, scan, 0) != 0) {
					start_production(e, scan, (char*) 0x67dc88, msg);
					goto after_start;
				}
				break;
			}
		}
	}

	for (i = 0; i < 0x20; i++) {
		order[i] = i;
	}
	for (i = 0; i < 0x20; i++) {
		r = gm_RandomMod(0x20) & 0xffff;
		t = order[i];
		order[i] = order[r];
		order[r] = t;
	}
	if (g_100b0ac > 0) {
		i = 0;
		do {
			prod = &g_100d0c0[order[i]];
			if ((prod->flags & 0x400) == 0 && can_start(e, stk, prod, 1)) {
				start_production(e, prod, (char*) 0x67dc6c, msg);
				goto after_start;
			}
			i++;
		} while (i < g_100b0ac);
	}
	if (g_100b0ac > 0) {
		i = 0;
		do {
			prod = &g_100d0c0[order[i]];
			if ((prod->flags & 0x400) == 0 && can_start(e, stk, prod, 0)) {
				start_production(e, prod, (char*) 0x67dc38, msg);
				goto after_start;
			}
			i++;
		} while (i < g_100b0ac);
	}
	e->item = 0;

after_start:
	ai_RequestProductionGoods(rec);
	ai_PlanResourceRestock(e, rec);

	for (prod = g_100d0c0, i = 0; i < g_100b0ac; i++, prod = &g_100d0c0[i]) {
		if ((prod->flags & 8) != 0) {
			for (k = 0; k < 4; k++) {
				id = *(int*) ((char*) prod + 4 + k * 4);
				if (*(int*) (g_100b0e8 + id * 0x40) <
				    (int) ((OBJECT_PROTOTYPE *)type_entry(prod->goods_id))->ingredient_amounts[k]) {
					prod->flags &= ~8;
				}
			}
		}
	}
	for (prod = g_100d0c0, i = 0; i < g_100b0ac; i++, prod = &g_100d0c0[i]) {
		if ((prod->flags & 0x400) != 0) {
			prod->flags &= ~8;
		}
	}
	for (res = (Res483f20*) g_100b0c4, i = 0; i < ai_ResourceCount; i++, res = (Res483f20*) ((char*) res + 0x40)) {
		if ((res->flags & 0x400) != 0 && (res->flags & 0x10) != 0 && res->id >= 0) {
			g_100d0c0[res->id].flags |= 0x10;
		}
	}

	if (g_100dc20 == e->root && g_100dc38 < 4) {
		i = 0;
		do {
			if (g_100b0ac <= i) {
				break;
			}
			memcpy((char*) 0x100dc60 + g_100dc38 * 0x58, &g_100d0c0[i], 0x58);
			for (k = 0; k < 4; k++) {
				id = *(int*) ((char*) &g_100d0c0[i] + 4 + k * 4);
				if (id >= 0) {
					memcpy((char*) 0x100df20 +
						   (g_100dc40[g_100dc38] + g_100dc38 * 4) * 0x40,
					       (char*) 0x100b0c0 + id * 0x40, 0x40);
					g_100dc40[g_100dc38]++;
				}
			}
			g_100dc38++;
			i++;
		} while (g_100dc38 < 4);
	}

	ai_CancelBlockedActions(e, 4);

	built = 0;
	for (slot = g_7f4ca0; slot < (char*)&((ENTITY_RECORD*)g_7f4ca0)[0x300]; slot = (char*)((ENTITY_RECORD*)slot + 1)) {
		if (*(unsigned char*) (slot + 8) <= 0) {
			continue;
		}
		if (*(unsigned short*) slot == 0xffff) {
			continue;
		}
		if (*(char*) (slot + 2) == 0x0a) {
			continue;
		}
		if (*(int*) (slot + 0x16c) != e->root) {
			continue;
		}
		if (*(char*) (slot + 0x165) == 0) {
			continue;
		}
		if (*(int*) (slot + 0x184) == 0) {
			continue;
		}
		if (*(int*) (*(int*) (slot + 0x184) + 0x2c) != *(int*) (*(int*) (slot + 0x16c) + 1)) {
			continue;
		}
		p = *(char**) (slot + 0x17c);
		if (p != 0 && *p != 4) {
			continue;
		}
		he_AssignActionSlot(e->root, 0, *(unsigned short*) slot, 0);
		built++;
	}
	if (g_100dc20 == e->root) {
		g_100dc34 = built;
	}

	n = 0;
	for (prod = g_100d0c0, i = 0; i < g_100b0ac; i++, prod = &g_100d0c0[i]) {
		if ((prod->flags & 8) != 0) {
			n++;
		}
		if ((prod->flags & 0x10) != 0) {
			n++;
		}
	}
	if (n >= built) {
		n = built;
	}
	if (built == 0 || n == 0) {
		ai_MeisterCollectTrans(e);
		ai_MeisterTrade(e, rec);
		return;
	}

	for (prod = g_100d0c0, i = 0; i < g_100b0ac; i++, prod = &g_100d0c0[i]) {
		plan.ent = (int) e;
		plan.entry = (int) prod;
		if ((prod->flags & 0x10) != 0) {
			if ((prod->flags & 0x400) == 0) {
				continue;
			}
			plan.kind = 0x8c;
			ai_DispatchMeisterAction(&plan);
		} else if ((prod->flags & 8) != 0) {
			plan.kind = 4;
			ai_DispatchMeisterAction(&plan);
		} else {
			continue;
		}
		if (g_100dc20 == e->root && g_100dc3c < 4) {
			memcpy((char*) 0x100ddc0 + g_100dc3c * 0x58, prod, 0x58);
			g_100dc3c++;
		}
	}
	ai_MeisterCollectTrans(e);
	ai_MeisterTrade(e, rec);
}
