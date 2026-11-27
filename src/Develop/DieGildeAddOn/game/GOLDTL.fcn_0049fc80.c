#include "Develop/DieGildeAddOn/game/entity_record.h"









typedef struct Rec18 {
	char pad0[8];
	unsigned char x8;
	char pad9[0xf];
} Rec18;
// SIZE 0x18



int __cdecl amt_GetRoleTemplate(int idx, Rec18* out);
#include "Develop/DieGildeAddOn/game/aemter.h"
int __cdecl amt_CollectOfficeCandidates(int k, int max, ENTITY_RECORD** out);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl fcn_004a5340(ENTITY_RECORD* e, int a, int* b, int c, float r, int* out);

/* ADDRESS: GOLDTL 0x0049fc80 */
ENTITY_RECORD* __cdecl ai_PickOfficeRival(ENTITY_RECORD* subject)
{
	ENTITY_RECORD* list[5];
	Rec18 roleTmpl;
	Rec18 rivalTmpl;
	ENTITY_RECORD* best;
	ENTITY_RECORD* candidate;
	float favor;
	int i;

	best = 0;
	if (subject->unk_165[1] == 0) {
		float bestFavor;

		amt_GetRoleTemplate(subject->unk_165[2], &roleTmpl);
		for (i = 0; i < 768; i++) {
			candidate = ((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[i]);
			if (candidate->unk_165[1] != 0 && srv_GetEntityOfficeSlot((unsigned char*) candidate, &roleTmpl, &rivalTmpl) != 0 && roleTmpl.x8 <= 1) {
				if (best == 0) {
					best = candidate;
					bestFavor = gm_CalcEntityFavor(subject->entity_index, candidate->entity_index, 1);
				} else {
					favor = gm_CalcEntityFavor(subject->entity_index, candidate->entity_index, 1);
					if (favor < bestFavor) {
						bestFavor = favor;
						best = candidate;
					}
				}
			}
		}
	} else {
		if (subject->unk_165[3] != 0) {
			int candidateCount;
			float bestFavor;

			candidateCount = amt_CollectOfficeCandidates(subject->unk_165[3], 5, list);
			if (candidateCount != 0) {
				for (i = 0; i < candidateCount; i++) {
					if (list[i] != subject) {
						if (best == 0) {
							best = list[i];
							bestFavor = gm_CalcEntityFavor(subject->entity_index, best->entity_index, 1);
						} else {
							favor = gm_CalcEntityFavor(subject->entity_index, list[i]->entity_index, 1);
							if (favor < bestFavor) {
								best = list[i];
								bestFavor = favor;
							}
						}
					}
				}
				if (best != 0) {
					if (candidateCount * 8.0f + 52.0f < bestFavor) {
						best = 0;
					}
				}
			}
		}
		if (best == 0) {
			int mask;
			int idx;

			mask = 0xc00;
			if (fcn_004a5340(subject, 1, &mask, 0, 25.0f, &idx) != 0) {
				return ((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[(unsigned short) idx]);
			}
		}
	}
	return best;
}
