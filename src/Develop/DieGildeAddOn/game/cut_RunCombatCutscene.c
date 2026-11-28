/* Guard shift selection: validates the party's two linked id lists, then
 * either animates the choice (cutscene mode) or runs the modal dialog. */

typedef struct Ent {
	unsigned short id;
	char pad2[6];
	unsigned char live;
} Ent;

/* 0xb8-byte entity query accumulator filled by fcn_0050de80. */
typedef struct Query {
	int count;
	int f4;
	char pad8[0xa8];
	int total;
	int fbc;
} Query;

typedef struct COMBAT_CUTSCENE_DLG {
	char pad0[0xc];
	int rec;
	char pad10[4];
	int actor;
	char pad18[0x1c];
	int first;
	int second;
	char pad3c[0x40];
	unsigned char flags;
	char pad7d[3];
	int list_a[16];
	int list_b[16];
	int list_c[3];
	int owner;
} COMBAT_CUTSCENE_DLG;
#include "Develop/DieGildeAddOn/game/client_data.h"
int __cdecl cut_GetRandSeed(void);
void __cdecl cut_SetRandSeed(int);
Ent* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_FindRecordById(int);
void __cdecl gm_CalcEntityInventoryStats(int, Query*);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
float __cdecl gm_CalcCombatStrength(Ent*);
void __cdecl gm_CheckCombatGearWear(Ent*);
int __cdecl _ftol(void);
unsigned short __cdecl gm_RandomMod(int);
float __cdecl gm_ApplyEntityHealthDelta(unsigned short, int);
void __cdecl cut_SetupBattleArena(COMBAT_CUTSCENE_DLG*);
void __cdecl cut_RefreshCombatContextCharacters(void);
void __cdecl cut_PlaceCombatTeamAtDummies(int*, int);
void __cdecl cut_RunGfxCutscene(COMBAT_CUTSCENE_DLG*);
void __cdecl d3_UpdateDaylightPhase(void*);
void __cdecl d3_BlendSceneLightingPreset(int, int, float, int);
void __cdecl cut_RunCombatStartDialog(COMBAT_CUTSCENE_DLG*);
void __cdecl cut_RunTurnRound(COMBAT_CUTSCENE_DLG*, int);
void __cdecl d2_DestroyElement(int);
void __cdecl d2_ShowCombatEndCutscene(COMBAT_CUTSCENE_DLG*);
void __cdecl cut_RunCombatFlightOutro(COMBAT_CUTSCENE_DLG*);
void __cdecl cut_CleanupCombatScene(COMBAT_CUTSCENE_DLG*);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl d2_ShowMessageBox(char*, unsigned int);
int __cdecl fcn_00502cd0(int, int, int, ...);
void __cdecl gm_TransferAndSellAssets(int, int, int, int);
void __cdecl cut_PlunderBuildingCarts(COMBAT_CUTSCENE_DLG*, int, int, int, float);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLDTL 0x004d77e0 */
void __cdecl cut_RunCombatCutscene(COMBAT_CUTSCENE_DLG* p)
{
	int changed;
	int flag;
	int saved;
	int i;
	int e;
	int v;
	int w;
	int t;
	Ent* ep;
	Query q;
	char buf[0x800];

	flag = 0;
	saved = cut_GetRandSeed();
	changed = 0;
	for (i = 0; i < 0x10; i++) {
		if (p->list_a[i] != -1 && gm_LookupEntityRecordById(p->list_a[i]) == 0) {
			flag = 1;
			p->list_a[i] = -1;
		}
	}
	for (i = 0; i < 0x10; i++) {
		if (p->list_b[i] != -1) {
			if (gm_LookupEntityRecordById(p->list_b[i]) == 0) {
				flag = 1;
				p->list_b[i] = -1;
			} else {
				changed++;
			}
		}
	}
	if (p->flags & 1) {
		for (i = 0; i < 3; i++) {
			if (p->list_c[i] != -1) {
				e = gm_FindRecordById(p->list_c[i]);
				if (e == 0 || (gm_CalcEntityInventoryStats(e, &q), q.total <= 0)) {
					flag = 2;
				}
			}
		}
	}
	if (gm_StartFilteredEntitySearch(1, 1, p->owner) == 0 || flag == 2 || changed == 0) {
		return;
	}
	if (*(int*) &cut_SkipMode == 0) {
		*(int*) 0x68bfbc = 0xc8;
		*(int*) 0x68b79c = p->rec;
		cut_SetupBattleArena(p);
		cut_RefreshCombatContextCharacters();
		cut_PlaceCombatTeamAtDummies(p->list_b, 0x68becc);
		cut_PlaceCombatTeamAtDummies(p->list_a, 0x68bec8);
		cut_RunGfxCutscene(p);
		if (*(int*) 0x774804 != 0) {
			d3_BlendSceneLightingPreset(2, 0, 1.0f, 1);
		} else {
			d3_UpdateDaylightPhase((void*) &gm_GameTime);
		}
		*(int*) &cut_CombatCancelledEntity = 0;
		*(int*) &cut_CombatResolved = 0;
		*(int*) &cut_PlunderedAmount = 0;
		cut_RunCombatStartDialog(p);
		cut_SetRandSeed(saved);
		cut_RefreshCombatContextCharacters();
		cut_RefreshCombatContextCharacters();
		cut_RunTurnRound(p, 0);
		if (*(int*) &cut_CombatCancelledEntity == 0 && *(int*) &cut_CombatResolved == 0) {
			cut_RunTurnRound(p, 0);
		}
		if (*(int*) &cut_CombatResolved == 0) {
			for (t = 0x9b4908; t < 0x9b4a48; t += 0x14) {
				if (*(int*) t != -1) {
					d2_DestroyElement(*(int*) t);
				}
				*(int*) t = -1;
				*(int*) (t - 4) = 0;
				*(int*) (t + 4) = 0;
			}
			d2_ShowCombatEndCutscene(p);
			cut_RunCombatFlightOutro(p);
		} else if (*(int*) &cut_PlunderedAmount != 0 && *(char*) (*(int*) &cut_CombatDefenderEntity + 2) == 6) {
			v = 0;
			w = gm_StartFilteredEntitySearch(1, 1, *(int*) (*(int*) 0x772eb4 + 0x10c));
			if (w != 0) {
				v = fcn_00502cd0(*(int*) (w + 0x5d), 2, 6, 0, 0x116);
			}
			if (*(int*) &cut_PlunderedAmount > 0) {
				if (v == 0) {
					io_FormatTextBuffer(buf, 0x1144, *(int*) &cut_PlunderedAmount);
				} else {
					io_FormatTextBuffer(buf, 0x1145, *(int*) &cut_PlunderedAmount);
				}
			} else {
				io_FormatTextBuffer(buf, 0x1146);
			}
			d2_ShowMessageBox(buf, 0x10);
		}
		cut_CleanupCombatScene(p);
		return;
	}
	changed = 0;
	saved = 0;
	*(int*) &cut_CombatDefenderEntity = (int) gm_LookupEntityRecordById(p->first);
	*(int*) 0x772e98 = (int) gm_LookupEntityRecordById(p->second);
	for (i = 0; i < 0x10; i++) {
		if (p->list_a[i] != -1) {
			ep = gm_LookupEntityRecordById(p->list_a[i]);
			if (ep != 0 && ep->live != 0 && ep->live != 4) {
				changed = (int) (gm_CalcCombatStrength(ep) + changed);
				gm_ApplyEntityHealthDelta(ep->id, gm_RandomMod(10) * -20);
			}
		}
	}
	for (i = 0; i < 0x10; i++) {
		if (p->list_b[i] != -1) {
			ep = gm_LookupEntityRecordById(p->list_b[i]);
			if (ep != 0 && ep->live != 0 && ep->live != 4) {
				saved = (int) (gm_CalcCombatStrength(ep) + saved);
				gm_ApplyEntityHealthDelta(ep->id, gm_RandomMod(10) * -20);
			}
		}
	}
	v = gm_RandomMod(0x1e) + saved;
	w = gm_RandomMod(0x1e) + changed;
	if (v > w) {
		changed = *(int*) &cut_CombatDefenderEntity;
	} else {
		changed = *(int*) 0x772e98;
	}
	for (i = 0; i < 0x10; i++) {
		if (p->list_a[i] != -1 && (ep = gm_LookupEntityRecordById(p->list_a[i])) != 0) {
			gm_CheckCombatGearWear(ep);
		}
	}
	for (i = 0; i < 0x10; i++) {
		if (p->list_b[i] != -1 && (ep = gm_LookupEntityRecordById(p->list_a[i])) != 0) {
			gm_CheckCombatGearWear(ep);
		}
	}
	if (p->flags & 2) {
		if (changed == *(int*) &cut_CombatDefenderEntity) {
			v = gm_StartFilteredEntitySearch(1, 1, p->owner);
			w = gm_StartFilteredEntitySearch(1, 1, p->actor);
			gm_TransferAndSellAssets(w, v, *(int*) &cut_CombatDefenderEntity, *(int*) 0x772e98);
		}
		return;
	}
	if (p->flags & 4) {
		return;
	}
	if (!(p->flags & 1)) {
		return;
	}
	if (changed == *(int*) &cut_CombatDefenderEntity) {
		v = gm_StartFilteredEntitySearch(1, 1, p->owner);
		cut_PlunderBuildingCarts(p, v, *(int*) &cut_CombatDefenderEntity, *(int*) 0x772e98, 100.0f);
	}
}
