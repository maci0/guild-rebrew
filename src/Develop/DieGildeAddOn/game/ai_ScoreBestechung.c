#include "Develop/DieGildeAddOn/game/game_data.h"
extern float flt_0_0;
extern float g_6628ac;

#include "Develop/DieGildeAddOn/game/client_method_registry.h"















typedef struct Rate {
	float f;
	int x4;
	int x8;
} Rate;

typedef struct Actor {
	unsigned short w0;
	char pad2[2];
	int id4;
	char pad8[0x88];
	Rate rate[13];
	char pad12c[4];
	unsigned char kind;      /* 0x130 */
	char pad131[0x166 - 0x131];
	unsigned char kind166;   /* 0x166 */
	unsigned char f167;
	unsigned char f168;      /* 0x168 */
} Actor;

typedef struct Entry {
	char pad0[0xb0];
	int id;                  /* 0xb0 */
	int val;                 /* 0xb4 */
	int ref1;                /* 0xb8 */
	int ref2;                /* 0xbc */
} Entry;

extern AM_METHOD am_Methods[];
extern char* gm_RichterKatholisch;
extern char* gm_RichterEvangelisch;
extern char* ai_FeudTargetEntity;

char* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
char* __cdecl he_StartHandlungSearch(int type, int a, int b);
char* __cdecl he_fn_Handlung(void);
int __cdecl gm_GetLawEntry(int idx, void* dst);
int __cdecl ai_ComputeBaseActionScore(float* a0, float* a1, int idx, Actor* e, int a4,
	char* a5, int a6);
int __cdecl ai_ComputeActionScore(float* a0, float* a1, int idx, Actor* e, int* rec);

/* Prices the stored goods of the selected warehouse and reports the
   cheapest one as action type 7; otherwise falls back to the plain
   building-deal calculators. */
/* ADDRESS: GOLDTL 0x004964e0 */
int __cdecl ai_ScoreBestechung(float* firstScore, float* secondScore, int idx, Actor* actor, int busy,
	char* resultData, int extra)
{
	AM_METHOD* method;
	Entry* entry;
	char* sv[3];
	char* chosen;
	float fv[3];
	float best;
	int bi;
	int i;
	int v;
	int w;
	int rec[9];

	if (busy != 0) {
		*firstScore = -1e30f;
		*secondScore = -1e30f;
		return 0;
	}
	*firstScore = 0.0f;
	*secondScore = 0.0f;
	method = &am_Methods[idx];
	if (actor->f168 != 0) {
		goto calc;
	}
	if (actor->kind166 != 0xd) {
		v = gm_RichterKatholisch != 0 ? *(int*) (gm_RichterKatholisch + 4) : -1;
		w = gm_RichterEvangelisch != 0 ? *(int*) (gm_RichterEvangelisch + 4) : -1;
		for (entry = (Entry*) he_StartHandlungSearch(1, 0, 0x2c); entry != 0;
			entry = (Entry*) he_fn_Handlung()) {
			if (entry->id != actor->id4) {
				continue;
			}
			if (entry->val == v || entry->val == w) {
				break;
			}
			fv[0] = 100.0f;
			fv[1] = 100.0f;
			fv[2] = 100.0f;
			best = 100.0f;
			bi = -1;
			sv[0] = gm_LookupEntityRecordById(entry->val);
			sv[1] = gm_LookupEntityRecordById(entry->ref1);
			sv[2] = gm_LookupEntityRecordById(entry->ref2);
			if (sv[0] != 0 && sv[0] != ai_FeudTargetEntity) {
				fv[0] = gm_CalcEntityFavor(actor->w0, *(unsigned short*) sv[0], 1);
			}
			if (sv[1] != 0 && sv[1] != ai_FeudTargetEntity) {
				fv[1] = gm_CalcEntityFavor(actor->w0, *(unsigned short*) sv[1], 1);
			}
			if (sv[2] != 0 && sv[2] != ai_FeudTargetEntity) {
				fv[2] = gm_CalcEntityFavor(actor->w0, *(unsigned short*) sv[2], 1);
			}
			for (i = 0; i < 3; i++) {
				if (fv[i] < best) {
					best = fv[i];
					bi = i;
				}
			}
			if (bi != -1) {
				chosen = sv[bi];
				resultData[0] = 7;
				*(int*) (resultData + 4) = *(int*) (chosen + 4);
				*(int*) (resultData + 8) = 1;
				goto calc;
			}
			goto fallback;
		}
	}
fallback:
	gm_GetLawEntry(0x10, rec);
	if (rec[6] == 0) {
		return ai_ComputeBaseActionScore(firstScore, secondScore, idx, actor, 0, resultData, extra);
	}
	return ai_ComputeActionScore(firstScore, secondScore, idx, actor, rec);
calc:
	for (i = 0; i < 4; i++) {
		if (method->effects[i].value > 0.0f) {
			*firstScore += method->effects[i].type == actor->kind
				? actor->rate[method->effects[i].type].f * method->effects[i].value * 0.02f
				: actor->rate[method->effects[i].type].f * method->effects[i].value * 0.01f;

		}
		if (method->other_effects[i].value > 0.0f) {
			if (method->other_effects[i].type == actor->kind) {
				*secondScore += actor->rate[method->other_effects[i].type].f * method->other_effects[i].value * 0.02f;
			} else {
				*secondScore += actor->rate[method->other_effects[i].type].f * method->other_effects[i].value * 0.01f;
			}

		}
	}
	return 1;
}
