/* Market supervisor tick: refills the per-player market stock (g_85ab90),
 * re-prices the open slots and runs the trade lager cycles over the three
 * market halls starting at 0x868354.
 *
 * The native frame (0x1a8, no EBP frame) packs nine four/eight byte scratch
 * slots, one 0x80 slot record and one 0xf0 spare buffer; the untyped scratch
 * slots are reused with different meanings in the three passes, so they are
 * named after the pass that owns them. */
#include "Develop/DieGildeAddOn/game/season_slots.h"
#include <string.h>

/* g_7f4c00: 14-byte market stamp, word view of the second field is compared. */
#include "Develop/DieGildeAddOn/game/game_timestamp.h"









/* one market slot record, 0x80 bytes */
typedef struct {
	unsigned short id;
	short pad2;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
	int f18;
	int f1c;
	float f20;
	float f24;
	float f28;
	float f2c;
	int f30;
	int f34;
	float f38;
	char pad3c[0x44];
} MarktSlot;

extern char* gm_MarketEntity;
extern unsigned char gm_ActiveTownIndex;
extern char* gm_CityEntity;
extern char* lpObjektePROT;
extern unsigned char gm_ClientModeFlags;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
extern float flt_0_0;
extern float g_662948;


extern double dbl_3_0;
extern double g_6629c8;
extern double dbl_0_75;
extern double g_664468;
extern double g_665dd0;

int __cdecl gm_GetElapsedMinutes(void*, void*);
void __cdecl he_FreeAction(char*);
int __cdecl gm_GetSeasonTreasury(int, unsigned char);
void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
char* __cdecl gm_FindCityItemHolder(int);
unsigned short* __cdecl fcn_00502cd0(int, int, int, ...);
int __cdecl gm_GetMsgField(void*, void*);
int __cdecl gm_RandomMod(unsigned short);
float __cdecl gm_RandomFloat01(void);
void __cdecl cm_SendSellObjekt(int, int, int, int, unsigned char, int);
int __cdecl cm_SendMarktSlotDelta(MarktSlot*, unsigned char);
float __cdecl gm_CalcMarketSlotPrice(int, int);
char* __cdecl gm_FindKind47ByOwner(int);
void __cdecl gm_AddTime(void*, int, int, int);
void __cdecl he_SetActionSubject(char*, int);
int __cdecl gm_eval_SlotVoll(char*, int, int);
int __cdecl fcn_64d41a(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x00568060 */
void __cdecl he_RunMarktSupervisor(char* action)
{
	union { float f; int n; } uf;
	int i;
	float g;
	union { int n; char* p; } ub;
	union { int n; char* p; } up;
	double d;
	int v;
	char* lager;
	int t;
	MarktSlot rec;
	char scratch[0x100];
	MarktSlot* slot;
	char* ent;
	char* q;
	unsigned char kind;
	char* bar;
	char* pat;
	char* hall;

	if (gm_MarketEntity == 0) {
		he_FreeAction(action);
		return;
	}
	v = gm_GetElapsedMinutes((void*) (action + 0x60), (void*) &gm_GameTime);
	if ((unsigned short) gm_GameTime.b > 0x14) {
		he_FreeAction(action);
		return;
	}
	if (v == 0) {
		return;
	}
	*(GAME_TIMESTAMP*) (action + 0x60) = *(GAME_TIMESTAMP*) &gm_GameTime;
	if (*(int*) (action + 0x70) < -2) {
		return;
	}
	if (*(int*) (action + 0x70) < 0) {
		he_SetActionSubject(action, *(unsigned short*) gm_CityEntity);
		*(int*) (action + 0x70) = 0;
		return;
	}
	if (*(int*) (action + 0x70) != 0) {
		return;
	}
	if (gm_GetSeasonTreasury((int) gm_CityEntity, gm_ActiveTownIndex) < 0x4e2000) {
		cm_RequestMoveCredits(*(int*) (gm_CityEntity + 4), -1, gm_ActiveTownIndex, 0x4e2000);
	}
	/* pass 1: refill the player's own stock */
	for (i = 0; i < 0x55; i++) {
		slot = (MarktSlot*)&((MARKET_STOCK_SLOT*)(gm_MarketStockTable + gm_ActiveTownIndex * 0x2a90))[i];
		if (((MARKET_STOCK_SLOT*)slot)->objekt_id == 0) {
			continue;
		}
		memcpy(&rec, slot, 0x80);
		if (((MARKET_STOCK_SLOT*)slot)->active == 0) {
			continue;
		}
		kind = *(unsigned char*) &((OBJECT_PROTOTYPE*) lpObjektePROT)[((MARKET_STOCK_SLOT*)slot)->objekt_id].kind;
		if (kind != 0x25 && kind != 0x17) {
			continue;
		}
		ent = gm_FindCityItemHolder(rec.id);
		if (ent == 0) {
			fcn_64d41a(scratch, "Could not find markt-lager:%s",
			    *(char**) (0x14a79c0 + rec.id * 8));
			continue;
		}
		q = (char*) fcn_00502cd0(*(int*) (ent + 0x14), 2, 6, 0,
		    rec.id);
		if (q != 0) {
			ub.n = gm_GetMsgField(ent, q);
		} else {
			ub.n = 0;
		}
		gm_RandomMod(10);
		d = (double) v * g_665dd0;
		uf.f = (float) (rec.f34 * 0.0714285746f * d);
		up.n = gm_RandomMod(100) & 0xffff;
		uf.f = (up.n + 20.0f) * uf.f * 0.01f;
		if (uf.f != flt_0_0) {
			if (flt_1_0 > uf.f) {
				uf.f = 1.0f;
			}
		}
		if (ub.n < rec.f34 * g_662908) {
			rec.f10 = (int) (rec.f10 + uf.f);
			if (rec.f20 * g_662908 < rec.f24) {
				cm_SendSellObjekt(*(int*) (ent + 2), -1,
				    rec.id, (int) uf.f, gm_ActiveTownIndex, 0);
				rec.f24 = rec.f34 * 0.0714285746f * d * g_662948 + rec.f24;
			}
		} else if (ub.n > rec.f34 * dbl_0_75) {
			uf.f = (float) (rec.f34 * 0.0714285746f * d);
			rec.f24 = rec.f24 - uf.f * flt_0_6;
			if (rec.f20 * 0.25 > rec.f24) {
				rec.f24 = rec.f20 * 0.25;
			}
			if (flt_1_0 > rec.f24) {
				rec.f24 = 1.0f;
			}
		}
		if (rec.f20 * 1.5f < rec.f24) {
			if (rec.f20 * 1.5f / rec.f24 < gm_RandomFloat01()) {
				rec.f24 = rec.f20 * 0.400000006f;
			}
		} else if (rec.f20 * 0.400000006f > rec.f24) {
			if (rec.f24 / (rec.f20 * 0.400000006f) < gm_RandomFloat01()) {
				rec.f24 = rec.f20 * 1.5f;
			}
		}
		if ((unsigned short) gm_RandomMod(100) > 0xa || (unsigned short) gm_GameTime.b == 0xc) {
			rec.f38 = gm_CalcMarketSlotPrice(gm_ActiveTownIndex, i);
		}
		cm_SendMarktSlotDelta(&rec, gm_ActiveTownIndex);
	}
	/* pass 2: price the slots the player does not hold */
	for (i = 0; i < 0x55; i++) {
		slot = (MarktSlot*)&((MARKET_STOCK_SLOT*)(gm_MarketStockTable + gm_ActiveTownIndex * 0x2a90))[i];
		if (((MARKET_STOCK_SLOT*)slot)->objekt_id == 0) {
			continue;
		}
		if (((MARKET_STOCK_SLOT*)slot)->active == 0) {
			continue;
		}
		kind = *(unsigned char*) &((OBJECT_PROTOTYPE*) lpObjektePROT)[((MARKET_STOCK_SLOT*)slot)->objekt_id].kind;
		if (kind == 0x25 || kind == 0x17) {
			continue;
		}
		memcpy(&rec, slot, 0x80);
		ent = gm_FindCityItemHolder(rec.id);
		if (ent == 0) {
			continue;
		}
		q = (char*) fcn_00502cd0(*(int*) (ent + 0x14), 1, 0,
		    rec.id);
		if (q != 0) {
			ub.n = gm_GetMsgField(ent, q);
		} else {
			ub.n = 0;
		}
		gm_RandomMod(10);
		g = (float) (rec.f20 * 0.0714285746f * ((double) v * g_665dd0));
		if (g != flt_0_0) {
			rec.f2c = rec.f2c + g;
		}
		if (!(rec.f2c < flt_1_0)) {
			t = (int) rec.f2c;
			rec.f2c = rec.f2c - (float) t;
		} else {
			t = 0;
		}
		if (ub.n != t) {
			t = ub.n;
		}
		if (ub.n < t) {
			t = ub.n;
		}
		if (t != 0) {
			rec.f14 = rec.f14 + t;
			rec.f24 = rec.f24 - g * flt_0_6;
			if (rec.f24 < g_6629c8) {
				rec.f24 = 1.0f;
			}
			ub.n = (int) (t * g_664468);
			if (ub.n < 1) {
				ub.n = 1;
			}
			if (gm_ClientModeFlags < 0x80) {
				cm_SendSellObjekt(-1, *(int*) (ent + 2),
				    rec.id, ub.n, gm_ActiveTownIndex, 0);
			}
		} else {
			rec.f24 = rec.f24 + g * g_662948;
			if (gm_RandomFloat01() < 0.25) {
				t = (gm_RandomMod(3) & 0xffff) + 1;
				cm_SendSellObjekt(*(int*) (ent + 2), -1,
				    rec.id, t, gm_ActiveTownIndex, 0);
				rec.f24 = g * flt_0_6 + rec.f24;
			}
		}
		if (rec.f20 * dbl_3_0 < rec.f24) {
			rec.f24 = rec.f20 * dbl_3_0;
		}
		if (rec.f20 * 1.5f < rec.f24) {
			if (rec.f20 * 1.5f / rec.f24 < gm_RandomFloat01()) {
				if (!((float) t < rec.f20 * g_662908)) {
					rec.f24 = rec.f20 * g_662948;
				} else {
					rec.f24 = rec.f20 * 0.400000006f;
				}
			}
		} else if (rec.f20 * 0.400000006f > rec.f24) {
			if (rec.f24 / (rec.f20 * 0.400000006f) < gm_RandomFloat01()) {
				if (t == 0) {
					rec.f24 = rec.f20 * 1.5f;
				} else {
					rec.f24 = rec.f20 * 1.2f;
				}
			}
		}
		if ((unsigned short) gm_RandomMod(100) > 0xa || (unsigned short) gm_GameTime.b == 0xc) {
			rec.f38 = gm_CalcMarketSlotPrice(gm_ActiveTownIndex, i);
		}
		cm_SendMarktSlotDelta(&rec, gm_ActiveTownIndex);
	}
	/* pass 3: the three trade lagers next to each market hall */
	i = 1;
	lager = gm_MarketStockTable + 0x2a90;
	bar = (char*) 0x868354;
	do {
		if (*bar == 0) {
			break;
		}
		q = gm_FindKind47ByOwner(i);
		if (q == 0) {
			goto next_lager;
		}
		hall = q;
		ent = (char*) fcn_00502cd0(*(int*) (hall + 0x5d), 2, 0, 0x1db, 6);
		if (ent == 0) {
			goto next_lager;
		}
		pat = lager;
		for (t = 0; t < 0x55; t++, pat += 0x80) {
			memcpy(&rec, pat, 0x80);
			if (rec.id == 0) {
				continue;
			}
			q = (char*) fcn_00502cd0(*(int*) (ent + 0x14), 1, 0,
			    rec.id);
			if (q == 0) {
				continue;
			}
			ub.n = gm_GetMsgField(ent, q);
			uf.n = ub.n;
			g = (float) (rec.f20 * 0.0714285746f * ((double) v * g_665dd0));
			rec.f2c = rec.f2c + g;
			if (rec.f2c < flt_1_0) {
				up.n = 0;
			} else {
				up.n = (int) rec.f2c;
				rec.f2c = rec.f2c - (float) up.n;
			}
			if (ub.n != 0) {
				if (up.n < ub.n) {
					ub.n = up.n;
				}
				if (ub.n > 0) {
					if (ub.n < 1) {
						ub.n = 1;
					}
					cm_SendSellObjekt(-1, *(int*) (ent + 2),
					    rec.id, ub.n, gm_ActiveTownIndex, 0);
				}
			}
			if (ub.n < g) {
				rec.f24 = rec.f24 + (g - ub.n) * 0.4;
				if (rec.f20 * dbl_3_0 < rec.f24) {
					rec.f24 = rec.f20 * dbl_3_0;
				}
			} else {
				rec.f24 = rec.f24 - g * g_662908;
				if (rec.f20 * 0.25 > rec.f24) {
					rec.f24 = rec.f20 * 0.25;
				}
				if (flt_1_0 > rec.f24) {
					rec.f24 = 1.0f;
				}
			}
			if (rec.f20 * 2.5f < rec.f24) {
				if (rec.f20 * 2.5f / rec.f24 < gm_RandomFloat01()) {
					rec.f24 = rec.f20 * g_662948;
				}
			} else if (rec.f20 * g_662948 > rec.f24) {
				if (rec.f24 / (rec.f20 * g_662948) < gm_RandomFloat01()) {
					rec.f24 = rec.f20 * 2.5f;
				}
			}
			if ((unsigned short) gm_RandomMod(100) > 0x4b) {
				rec.f38 = gm_CalcMarketSlotPrice(i, t);
			}
			cm_SendMarktSlotDelta(&rec, i);
		}
		ent = (char*) fcn_00502cd0(*(int*) (hall + 0x5d), 2, 0, 0x1dc, 6);
		if (ent == 0) {
			goto next_lager;
		}
		pat = lager;
		for (t = 0; t < 0x55; t++, pat += 0x80) {
			memcpy(scratch, pat, 0x80);
			if (((MarktSlot*) scratch)->id == 0) {
				continue;
			}
			q = (char*) fcn_00502cd0(*(int*) (ent + 0x14), 1, 0,
			    ((MarktSlot*) scratch)->id);
			if (q == 0) {
				continue;
			}
			g = (float) (((MarktSlot*) scratch)->f20 * 0.0714285746f
			    * ((double) v * g_665dd0));
			uf.n = gm_RandomMod(3) & 0xffff;
			uf.f = (float) uf.n + g;
			if (uf.f < flt_1_0) {
				uf.f = 1.0f;
			}
			ub.n = gm_eval_SlotVoll(ent,
			    ((MarktSlot*) scratch)->id, (int) uf.f);
			uf.f = (float) ub.n;
			ub.n = gm_GetMsgField(ent, q);
			if (ub.n > ((MarktSlot*) scratch)->f20 * g_662908) {
				cm_SendSellObjekt(*(int*) (ent + 2), -1,
				    ((MarktSlot*) scratch)->id,
				    (int) uf.f, gm_ActiveTownIndex, 0);
				((MarktSlot*) scratch)->f24 = g * g_662908
				    + ((MarktSlot*) scratch)->f24;
				if (((MarktSlot*) scratch)->f20 * dbl_3_0
				    < ((MarktSlot*) scratch)->f24) {
					((MarktSlot*) scratch)->f24 =
					    ((MarktSlot*) scratch)->f20 * dbl_3_0;
				}
			} else {
				((MarktSlot*) scratch)->f24 =
				    ((MarktSlot*) scratch)->f24 - g * 0.1;
				if (((MarktSlot*) scratch)->f20 * 0.25
				    > ((MarktSlot*) scratch)->f24) {
					((MarktSlot*) scratch)->f24 =
					    ((MarktSlot*) scratch)->f20 * 0.25;
				}
				if (flt_1_0 > ((MarktSlot*) scratch)->f24) {
					((MarktSlot*) scratch)->f24 = 1.0f;
				}
			}
			if ((unsigned short) gm_RandomMod(100) > 0x4b) {
				((MarktSlot*) scratch)->f38 = gm_CalcMarketSlotPrice(i, t);
			}
			cm_SendMarktSlotDelta((MarktSlot*) scratch, i);
		}
next_lager:
		i++;
		bar += 0x2f4;
		lager += 0x2a90;
	} while (bar < (char*) 0x868c30);
	if ((unsigned short) gm_GameTime.b >= 0x16) {
		he_FreeAction(action);
		return;
	}
	*(GAME_TIMESTAMP*) (action + 0x52) = *(GAME_TIMESTAMP*) &gm_GameTime;
	gm_AddTime(action + 0x52, 1, 0, 0);
	*(int*) (action + 0x70) = 0;
}
