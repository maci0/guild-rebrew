/* AI: a master decides to recruit thieves (Gesetze/slavery economy screen logic). */
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include <string.h>
#include <stdio.h>
#include "Develop/DieGildeAddOn/game/goods_plan.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
typedef struct GOLDTL_Msg481 {
	int f0;                         /* 0x00 */
	unsigned char f4;               /* 0x04 */
	char pad5[3];
	int f8;                         /* 0x08 */
	int fc;                         /* 0x0c */
	char pad10[0x18];
	int f28;                        /* 0x28 */
	int f2c;                        /* 0x2c */
	int f30;                        /* 0x30 */
	unsigned short f34;             /* 0x34 */
	unsigned char f36;              /* 0x36 */
	char pad37[1];
	int f38[8];                     /* 0x38 */
	int f58;                        /* 0x58 */
	int f5c;                        /* 0x5c */
	int f60;                        /* 0x60 */
	char pad64[0x1c];
	int f80;                        /* 0x80 */
	char pad84[0x74];
} GOLDTL_Msg481;                    /* SIZE 0xf8 */
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char gm_EntitySlotTable[];
extern unsigned short gm_GameTimeHour;
extern int gm_GameTime;
extern int gm_GameTimeSliceDword;
extern unsigned char* lpGebaeudePROT;
extern unsigned char* lpObjektePROT;
extern unsigned char* lpGebaeudeINST;
extern unsigned char gm_CrimeGrid[];
extern int ai_MeisterDebugState;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100dc24;
extern char* ai_TrackedGoodPlanEntries;
extern unsigned short* gm_CityEntity;
extern int gm_DifficultyLevel;

int __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_ResolveEntityById(int, int*, int, int);
void __cdecl ai_CollectGoodsResources(int, int);
void __cdecl ai_PlanMeisterSupplies(int, int, int);
void __cdecl ai_ArmMeisterWorkers(int, int);
void __cdecl fcn_00489250(int);
void __cdecl fcn_00489a70(int, int);
void __cdecl ai_ManageMeisterWorkers(int);
void __cdecl gm_TryAutoUpgradeBuildingSlots(int, int, int);
void __cdecl ai_RequestAusbauUpgrade(int, int, int);
void __cdecl ai_BuyStallGoods(int);
void __cdecl ai_FlagIdleWorkersForRecovery(int);
void __cdecl ai_DispatchWorkerRecovery(int);
void __cdecl ai_CalcAngriff(int, int);
int __cdecl gm_SearchTable67(int);
int __cdecl gm_PosToStatsGrid(int, int*, int*);
int __cdecl gm_GetBuildingProtLevel(unsigned char*);
int __cdecl gm_CalcOwnerAndStockValue(unsigned char*, int);
int __cdecl gm_AccumulateTyped2(unsigned char*);
int __cdecl gm_CheckEntityType(unsigned char*);
int __cdecl gm_GetBuildingTypeCategory(unsigned int);
int __cdecl he_HasNoActiveAction0x62(unsigned char*);
void __cdecl cm_SendCopyEntityData(GOLDTL_Msg481*);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
unsigned short __cdecl gm_RandomMod(int);
float __cdecl gm_RandomFloat01(void);


#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* ADDRESS: GOLDTL 0x004813b0 */
void __cdecl ai_CalcMeisterDiebe(unsigned char* rec)
{
	GOLDTL_Msg481 msg;
	char text[0x400];
	float factor;
	float maxfactor;
	int match;
	int i;
	int cx;
	float best_score;
	int cy;
	int saved;
	char* owner;
	unsigned char* ent;
	int total;
	int found;
	int sel;
	int j;
	int n;
	unsigned char* e;
	unsigned char* best;
	unsigned char* handle;

	handle = 0;
	saved = (int) handle;
	found = fcn_00502cd0(*(int*) (*(int*) (rec + 0x16c) + 0x5d), 2, 6, 0, 0x116);
	for (;;) {
		if (found == 0) {
			break;
		}
		if (gm_ResolveEntityById(0, (int*) &ent, 0, *(int*) (found + 6)) != 0
		    && *(char*) (((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[(unsigned int) (unsigned short) *(unsigned short*) ent])) == 2) {
			handle = (unsigned char*) found;
		}
		found = gm_NextEntityQueryMatch();
		if (handle == 0) {
			continue;
		}
		break;
	}
	saved = (int) handle;
	if (handle == 0) {
		goto common;
	}
	ai_ProductionGoodsCount = 0;
	ai_ResourceCount = 0;
	ai_CollectGoodsResources((int) rec, (int) handle);
	ai_PlanMeisterSupplies((int) rec, (int) handle, *(int*) (*(int*) (rec + 0x16c) + 0x39));
	ai_ArmMeisterWorkers((int) rec, (int) handle);
	if (ai_MeisterDebugState == *(int*) (rec + 0x16c) && g_100dc38 < 4) {
		j = 0;
		n = ai_ResourceCount;
		e = (unsigned char*) ai_ResourceRequests;
		do {
			if (j >= n) {
				break;
			}
			memcpy((void*) (ai_TrackedGoodPlanEntries + g_100dc38 * 0x40), e, 0x40);
			e = e + 0x40;
			g_100dc38 = g_100dc38 + 1;
			j = j + 1;
		} while (g_100dc38 < 4);
	}
	fcn_00489250((int) rec);
	fcn_00489a70((int) rec, saved);
common:
	ai_ManageMeisterWorkers((int) rec);
	gm_TryAutoUpgradeBuildingSlots(saved, (int) rec, 10);
	ai_RequestAusbauUpgrade(saved, (int) rec, 10);
	ai_BuyStallGoods((int) rec);
	if (fcn_00502cd0(*(int*) (*(int*) (rec + 0x16c) + 0x5d), 2, 6, 0, 0x60) != 0) {
		ai_FlagIdleWorkersForRecovery((int) rec);
	}
	ai_DispatchWorkerRecovery((int) rec);
	if (gm_GameTimeHour <= 6
	    || (*(int*) (rec + 4) + ((unsigned int) gm_GameTimeHour & 0xffff)) % 3 != 0) {
		*(unsigned int*) (rec + 0x1b4) = *(unsigned int*) (rec + 0x1b4) & 0xffffffdf;
		return;
	}
	if ((*(unsigned int*) (rec + 0x1b4) & 0x20) != 0) {
		return;
	}
	match = 0;
	total = 0;
	*(unsigned int*) (rec + 0x1b4) = *(unsigned int*) (rec + 0x1b4) | 0x20;
	for (e = (unsigned char*) gm_EntitySlotTable; (int) e < 0x85a0a0; e = e + sizeof(ENTITY_RECORD)) {
		if (e[8] > 0 && *(unsigned short*) e != 0xffff && e[2] != 0x0a
		    && *(int*) (e + 0x16c) == *(int*) (rec + 0x16c)
		    && e[0x165] != 0
		    && (ent = *(unsigned char**) (e + 0x184)) != 0
		    && *(int*) (ent + 0x2c) == *(int*) (*(int*) (e + 0x16c) + 1)) {
			total = total + 1;
			if (*(int*) (e + 0x17c) == 0) {
				match = match + 1;
			}
		}
	}
	if (ai_MeisterDebugState == *(int*) (rec + 0x16c)) {
		g_100dc34 = match;
		if (*(int*) (rec + 0x1c0) != -1) {
			g_100dc24 = gm_SearchTable67(*(int*) (rec + 0x1c0));
		}
	}
	j = total >> 1;
	if (j >= total - j) {
		j = total - j;
	}
	if (match < j) {
		owner = (char*) (rec + 0x30);
		sprintf(text, "ai_CalcMeisterDiebe(): Meister %s hat gerade keine Leute...", owner);
		return;
	}
	{
		unsigned char type = *(unsigned char*) ((unsigned int) (*(unsigned short*) (*(int*) (rec + 0x16c) + 0x27)) * 0x21c + 0x7f4ca2);
		if (type == 6 || type == 7) {
			sel = gm_RandomMod(2) & 0xffff;
			if (sel != 0 && *(int*) (rec + 0x1c0) != -1 && (gm_RandomMod(2) & 0xffff) != 0) {
				goto L176c;
			}
		} else {
			if (gm_RandomFloat01() > 0.85 && match >= 3 && gm_GameTime >= 7 - gm_DifficultyLevel) {
				goto L1e70;
			}
			sel = gm_RandomMod(3) & 0xffff;
		}
	}
	if (sel == 1) {
		if (gm_RandomFloat01() < 0.95) {
			goto L2267;
		}
		owner = (char*) (rec + 0x30);
		sprintf(text, "ai_CalcMeisterDiebe(): Meister %s m\366chte entf\374hren", owner);
		maxfactor = 0;
		cy = 8;
		cx = 8;
		e = (unsigned char*) gm_CrimeGrid + 2;
L1723:
		best = e;
		j = 8;
L1727:
		{
			float f = (float) *(unsigned short*) (best - 2) * 0.125f + (float) *(unsigned short*) best;
			if (!(maxfactor > f)) {
				maxfactor = f;
			}
			goto L1e81;
		}
	}
	if (sel != 0) {
		goto L1e67;
	}

L176c:
	owner = (char*) (rec + 0x30);
	sprintf(text, "ai_CalcMeisterDiebe(): Meister %s m\366chte einbrechen", owner);
	if (*(int*) (rec + 0x1c0) != -1) {
		best = e = (unsigned char*) gm_SearchTable67(*(int*) (rec + 0x1c0));
		if (e == 0) {
			*(int*) (rec + 0x1c0) = -1;
		} else if (*(unsigned short*) (e + 0x27) == *(unsigned short*) (*(int*) (rec + 0x16c) + 0x27)) {
			*(int*) (rec + 0x1c0) = -1;
		}
	}
	if (*(int*) (rec + 0x1c0) == -1) {
		maxfactor = 0;
		cx = 8;
		cy = 8;
		{
			unsigned char* p;
			unsigned char* q;
			int b;
			for (p = (unsigned char*) gm_CrimeGrid + 2; (int) p < (int) (gm_CrimeGrid + 0xc2); p = p + 0x18) {
				q = p;
				for (b = 8; b != 0; b--) {
					float f = (float) *(unsigned short*) (q - 2) * 0.125f + (float) *(unsigned short*) q;
					if (!(maxfactor > f)) {
						maxfactor = f;
					}
					q = q + 0xc0;
				}
			}
		}
		if (maxfactor == 0.0f) {
			maxfactor = 1.0f;
		}
		best = 0;
		i = 0x100;
		e = lpGebaeudeINST;
		for (;;) {
			if (*e != 0) {
				unsigned char* bld = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned int)*e];
				unsigned short hid = *(unsigned short*) (e + 0x27);
				unsigned short hsel = *(unsigned short*) (*(int*) (rec + 0x16c) + 0x27);
				if (hid != hsel && hid != 0xffff && (e[0x5a] & 1) == 0
				    && hid != *gm_CityEntity
				    && gm_CheckEntityType(e) == 0
				    && *bld != '!'
				    && he_HasNoActiveAction0x62(e) != 0) {
					int node = *(int*) (e + 0x61);
					if (node == 0 || gm_PosToStatsGrid(node + 0x4c, &cx, &cy) == 0) {
						factor = 0;
					} else {
						int off = (cy + cx * 8) * 0x18;
						factor = 1.0f
						         - ((float) *(unsigned short*) (gm_CrimeGrid + off) * 0.125f
						            + (float) *(unsigned short*) (gm_CrimeGrid + off + 2))
						           / maxfactor;
					}
					j = gm_GetBuildingProtLevel(e);
					factor = (8.0f - (float) j) * factor * 0.5f;
					factor = (float) (gm_RandomMod(100) & 0xffff) * factor * 0.01;
					if (best != 0) {
						int a2 = gm_CalcOwnerAndStockValue(e, saved != 0);
						float fa = (float) a2 * factor;
						int b2 = gm_CalcOwnerAndStockValue(best, saved != 0);
						if (!(fa > (float) b2 * best_score)) {
							goto L1a0c2;
						}
					}
					best_score = factor;
					best = e;
				}
			}
L1a0c2:
			e = e + 0xa9;
			if (--i == 0) {
				break;
			}
		}
		if (best == 0) {
			*(int*) (rec + 0x1c0) = -1;
			goto L2267;
		}
		*(int*) (rec + 0x1c0) = *(int*) (best + 1);
	}
	if (best == 0) {
		goto L2267;
	}
	found = fcn_00502cd0(*(int*) (*(int*) (rec + 0x16c) + 0x5d), 1, 0, 0xca);
	for (;;) {
		if (found == 0) {
			goto Lcae;
		}
		if (*(int*) (found + 0x2a) == *(int*) (best + 1)) {
			j = *(unsigned char*) (found + 0x37);
			if (j >= 0x5f) {
				break;
			}
			sel = gm_RandomMod(0x14) & 0xffff;
			if ((float) *(unsigned char*) (found + 0x36) * 2.0f + (float) sel > (float) j) {
				goto Lcae;
			}
			break;
		}
		found = gm_NextEntityQueryMatch();
	}
	found = he_StartHandlungSearch(2, 0, 0x40, 3, *(int*) (*(int*) (rec + 0x16c) + 1));
	for (;;) {
		if (found == 0) {
			break;
		}
		if (*(int*) (found + 0xac) == *(int*) (best + 1)) {
			goto Lc7e;
		}
		found = he_fn_Handlung();
	}
	found = he_StartHandlungSearch(2, 0, 0x3f, 3, *(int*) (*(int*) (rec + 0x16c) + 1));
	for (;;) {
		if (found == 0) {
			break;
		}
		if (*(int*) (found + 0xac) == *(int*) (best + 1)) {
			goto Lc7e;
		}
		found = he_fn_Handlung();
	}
	owner = (char*) (rec + 0x30);
	sprintf(text, "ai_CalcMeisterDiebe(): Meister %s bricht bei '%s' ein", owner, (char*) (best + 5));
	memset(&msg, 0, sizeof msg);
	{
		int h = *(int*) (rec + 0x16c);
		msg.f4 = 0x3f;
		msg.f8 = *(int*) ((unsigned int) (unsigned short) *(unsigned short*) (h + 0x27) * 0x21c + 0x7f4ca4);
		msg.fc = *(int*) (h + 1);
		msg.f28 = gm_GameTime;
		msg.f2c = *(int*) &gm_GameTimeHour;
		msg.f30 = gm_GameTimeSliceDword;
		msg.f34 = *(unsigned short*) 0x7f4c0c;
		msg.f36 = 1;
		msg.f58 = *(int*) (best + 1);
		msg.f5c = *(int*) (h + 1);
	}
	n = match;
	if (n > 7) {
		n = 8;
	}
	i = 0;
	if (n > 0) {
		unsigned char* p = (unsigned char*) 0x7f4e05;
		for (;;) {
			if ((int) p >= 0x85a205) {
				break;
			}
			if (*(unsigned short*) (p - 0x165) != 0xffff
			    && *(int*) (p + 7) == *(int*) (rec + 0x16c)
			    && *p != 0
			    && *(int*) (p + 0x17) == 0
			    && *(int*) (p + 0x1f) != 0
			    && *(int*) (*(int*) (p + 0x1f) + 0x2c) == *(int*) (*(int*) (p + 7) + 1)) {
				msg.f38[i] = *(int*) (p - 0x161);
				i = i + 1;
			}
			p = p + 0x21c;
			if (i >= n) {
				break;
			}
		}
	}
	if (i < 8) {
		for (; i < 8; i++) {
			msg.f38[i] = -1;
		}
	}
	if (msg.f38[0] != -1) {
		cm_SendCopyEntityData(&msg);
	}
	*(int*) (rec + 0x1c0) = -1;
	return;

Lc7e:
	owner = (char*) (rec + 0x30);
	sprintf(text, "ai_CalcMeisterDiebe(): Meister %s hat aber noch eine Spionage bei '%s' nicht beendet", owner, (char*) (best + 5));
	return;

Lcae:
	found = he_StartHandlungSearch(2, 0, 0x40, 3, *(int*) (*(int*) (rec + 0x16c) + 1));
	for (;;) {
		if (found == 0) {
			break;
		}
		if (*(int*) (found + 0xac) == *(int*) (best + 1)) {
			goto Le3e;
		}
		found = he_fn_Handlung();
	}
	found = he_StartHandlungSearch(2, 0, 0x3f, 3, *(int*) (*(int*) (rec + 0x16c) + 1));
	for (;;) {
		if (found == 0) {
			break;
		}
		if (*(int*) (found + 0xac) == *(int*) (best + 1)) {
			goto Le3e;
		}
		found = he_fn_Handlung();
	}
	owner = (char*) (rec + 0x30);
	sprintf(text, "ai_CalcMeisterDiebe(): Meister %s spioniert bei '%s'", owner, (char*) (best + 5));
	memset(&msg, 0, sizeof msg);
	{
		int h = *(int*) (rec + 0x16c);
		msg.f4 = 0x40;
		msg.f8 = *(int*) ((unsigned int) (unsigned short) *(unsigned short*) (h + 0x27) * 0x21c + 0x7f4ca4);
		msg.fc = *(int*) (h + 1);
		msg.f28 = gm_GameTime;
		msg.f2c = *(int*) &gm_GameTimeHour;
		msg.f30 = gm_GameTimeSliceDword;
		msg.f34 = *(unsigned short*) 0x7f4c0c;
		msg.f36 = 1;
		msg.f58 = *(int*) (best + 1);
		msg.f5c = *(int*) (h + 1);
	}
	n = match;
	if (n > 7) {
		n = 8;
	}
	i = 0;
	if (n > 0) {
		unsigned char* p = (unsigned char*) 0x7f4e05;
		for (;;) {
			if ((int) p >= 0x85a205) {
				break;
			}
			if (*(unsigned short*) (p - 0x165) != 0xffff
			    && *(int*) (p + 7) == *(int*) (rec + 0x16c)
			    && *p != 0
			    && *(int*) (p + 0x17) == 0
			    && *(int*) (p + 0x1f) != 0
			    && *(int*) (*(int*) (p + 0x1f) + 0x2c) == *(int*) (*(int*) (p + 7) + 1)) {
				msg.f38[i] = *(int*) (p - 0x161);
				i = i + 1;
			}
			p = p + 0x21c;
			if (i >= n) {
				break;
			}
		}
	}
	if (i < 8) {
		for (; i < 8; i++) {
			msg.f38[i] = -1;
		}
	}
	cm_SendCopyEntityData(&msg);
	return;

Le3e:
	owner = (char*) (rec + 0x30);
	sprintf(text, "ai_CalcMeisterDiebe(): Meister %s hat schon eine Spionage bei '%s' laufen", owner, (char*) (best + 5));
	return;

L1e67:
	if (sel != 3) {
		goto L225e;
	}
L1e70:
	ai_CalcAngriff((int) rec, (int) handle);
	goto L2267;

L1e81:
	best = best + 0xc0;
	if (--j != 0) {
		goto L1727;
	}
	e = e + 0x18;
	if ((int) e < (int) (gm_CrimeGrid + 0xc2)) {
		goto L1723;
	}
	if (maxfactor == 0.0f) {
		maxfactor = 1.0f;
	}
	best = 0;
	i = 0x100;
	e = lpGebaeudeINST;
	for (;;) {
		if (*e != 0) {
			int cat = gm_GetBuildingTypeCategory(*e);
			unsigned short hid = *(unsigned short*) (e + 0x27);
			unsigned short hsel = *(unsigned short*) (*(int*) (rec + 0x16c) + 0x27);
			if (hid != hsel && hid != 0xffff && (e[0x5a] & 1) == 0
			    && cat != 3 && cat != 5 && cat != 0) {
				ENTITY_RECORD* candidate = &((ENTITY_RECORD*) gm_EntitySlotTable)[hid];
				int q = (int) candidate->unk_16c;
				if ((q == 0 || *(unsigned short*) (q + 0x27) != hsel)
				    && candidate->entity_state < 8) {
					int node = *(int*) (e + 0x61);
					if (node == 0 || gm_PosToStatsGrid(node + 0x4c, &cx, &cy) == 0) {
						factor = 0;
					} else {
						int off = (cy + cx * 8) * 0x18;
						factor = 1.0f
						         - ((float) *(unsigned short*) (gm_CrimeGrid + off) * 0.125f
						            + (float) *(unsigned short*) (gm_CrimeGrid + off + 2))
						           / maxfactor;
					}
					factor = (float) (gm_RandomMod(100) & 0xffff) * factor * 0.01;
					if (best != 0) {
						int a2 = gm_AccumulateTyped2((unsigned char*) ((unsigned int) hid * 0x21c + 0x7f4ca0));
						float fa = (float) a2 * factor;
						int b2 = gm_AccumulateTyped2((unsigned char*) ((unsigned int) (unsigned short) *(unsigned short*) (best + 0x27) * 0x21c + 0x7f4ca0));
						if (!(fa > (float) b2 * best_score)) {
							goto L1a0c;
						}
					}
					best_score = factor;
					best = e;
				}
			}
		}
L1a0c:
		e = e + 0xa9;
		if (--i == 0) {
			break;
		}
	}
	if (fcn_00502cd0(*(int*) (*(int*) (rec + 0x16c) + 0x5d), 1, 0, 0x65) == 0
	    || best == 0
	    || *(int*) (*(int*) (rec + 0x16c) + 0x65) != -1) {
		goto L2267;
	}
	if (he_StartHandlungSearch(2, 0, 0x3c, 3, *(int*) (*(int*) (rec + 0x16c) + 1)) != 0) {
		return;
	}
	owner = (char*) (rec + 0x30);
	sprintf(text, "ai_CalcMeisterDiebe(): Meister %s entf\374hrt %s aus '%s'", owner,
	          (char*) (best + 5), (char*) ((unsigned int) (unsigned short) *(unsigned short*) (best + 0x27) * 0x21c + 0x7f4cd0));
	memset(&msg, 0, sizeof msg);
	{
		int h = *(int*) (rec + 0x16c);
		msg.f4 = 0x3c;
		msg.f8 = *(int*) ((unsigned int) (unsigned short) *(unsigned short*) (h + 0x27) * 0x21c + 0x7f4ca4);
		msg.fc = *(int*) (h + 1);
		msg.f28 = gm_GameTime;
		msg.f2c = *(int*) &gm_GameTimeHour;
		msg.f30 = gm_GameTimeSliceDword;
		msg.f34 = *(unsigned short*) 0x7f4c0c;
		msg.f36 = 1;
		msg.f58 = *(int*) ((unsigned int) (unsigned short) *(unsigned short*) (best + 0x27) * 0x21c + 0x7f4ca4);
		msg.f5c = *(int*) (best + 1);
		msg.f60 = *(int*) (h + 1);
	}
	n = MIN(match, gm_RandomMod(3) + 1);
	i = 0;
	if (n > 0) {
		unsigned char* p = (unsigned char*) 0x7f4e05;
		for (;;) {
			if ((int) p >= 0x85a205) {
				break;
			}
			if (*(unsigned short*) (p - 0x165) != 0xffff
			    && *(int*) (p + 7) == *(int*) (rec + 0x16c)
			    && *p != 0
			    && *(int*) (p + 0x17) == 0
			    && *(int*) (p + 0x1f) != 0
			    && *(int*) (*(int*) (p + 0x1f) + 0x2c) == *(int*) (*(int*) (p + 7) + 1)) {
				msg.f38[i] = *(int*) (p - 0x161);
				i = i + 1;
			}
			p = p + 0x21c;
			if (i >= n) {
				break;
			}
		}
	}
	if (i < 8) {
		for (; i < 8; i++) {
			msg.f38[i] = -1;
		}
	}
	if (msg.f38[0] != -1) {
		cm_SendCopyEntityData(&msg);
	}
	*(int*) (rec + 0x1c0) = -1;
	return;

L225e:
	if (sel <= 1) {
		return;
	}
L2267:
	owner = (char*) (rec + 0x30);
	sprintf(text, "ai_CalcMeisterDiebe(): Meister %s m\366chte Taschen dieben", owner);
	memset(&msg, 0, sizeof msg);
	{
		int h = *(int*) (rec + 0x16c);
		unsigned int id = (unsigned int) (unsigned short) *(unsigned short*) (h + 0x27);
		msg.f4 = 0x61;
		msg.f8 = *(int*) (id * 0x21c + 0x7f4ca4);
		msg.fc = *(int*) (h + 1);
		msg.f28 = gm_GameTime;
		msg.f2c = *(int*) &gm_GameTimeHour;
		msg.f30 = gm_GameTimeSliceDword;
		msg.f34 = *(unsigned short*) 0x7f4c0c;
		msg.f36 = 1;
		msg.f80 = *(int*) (id * 0x21c + 0x7f4ca4);
	}
	n = match;
	if (n > 7) {
		n = 8;
	}
	i = 0;
	if (n > 0) {
		unsigned char* p = (unsigned char*) 0x7f4e05;
		for (;;) {
			if ((int) p >= 0x85a205) {
				break;
			}
			if (*(unsigned short*) (p - 0x165) != 0xffff
			    && *(int*) (p + 7) == *(int*) (rec + 0x16c)
			    && *p != 0
			    && *(int*) (p + 0x17) == 0
			    && *(int*) (p + 0x1f) != 0
			    && *(int*) (*(int*) (p + 0x1f) + 0x2c) == *(int*) (*(int*) (p + 7) + 1)) {
				msg.f38[i] = *(int*) (p - 0x161);
				i = i + 1;
			}
			p = p + 0x21c;
			if (i >= n) {
				break;
			}
		}
	}
	if (i < 8) {
		for (; i < 8; i++) {
			msg.f38[i] = -1;
		}
	}
	if (msg.f38[0] != -1) {
		cm_SendCopyEntityData(&msg);
	}
	return;
}
