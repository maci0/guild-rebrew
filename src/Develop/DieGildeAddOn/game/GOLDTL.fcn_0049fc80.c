#include "Develop/DieGildeAddOn/game/entity_record.h"









typedef struct Rec18 {
	char pad0[8];
	unsigned char x8;
	char pad9[0xf];
} Rec18;
// SIZE 0x18



int __cdecl fcn_004e8b40(int idx, Rec18* out);
#include "Develop/DieGildeAddOn/game/aemter.h"
int __cdecl fcn_004e9310(int k, int max, ENTITY_RECORD** out);
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl fcn_004a5340(ENTITY_RECORD* e, int a, int* b, int c, float r, int* out);

/* ADDRESS: GOLDTL 0x0049fc80 */
ENTITY_RECORD* __cdecl fcn_0049fc80(ENTITY_RECORD* subject)
{
	ENTITY_RECORD* list[5];
	Rec18 q;
	Rec18 r;
	ENTITY_RECORD* best;
	ENTITY_RECORD* candidate;
	float d;
	int i;

	best = 0;
	if (subject->unk_165[1] == 0) {
		float bd;

		fcn_004e8b40(subject->unk_165[2], &q);
		for (i = 0; i < 768; i++) {
			candidate = ((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[i]);
			if (candidate->unk_165[1] != 0 && srv_GetEntityOfficeSlot((unsigned char*) candidate, &q, &r) != 0 && q.x8 <= 1) {
				if (best == 0) {
					best = candidate;
					bd = fcn_0050f980(subject->entity_index, candidate->entity_index, 1);
				} else {
					d = fcn_0050f980(subject->entity_index, candidate->entity_index, 1);
					if (d < bd) {
						bd = d;
						best = candidate;
					}
				}
			}
		}
	} else {
		if (subject->unk_165[3] != 0) {
			int n;
			float bd;

			n = fcn_004e9310(subject->unk_165[3], 5, list);
			if (n != 0) {
				for (i = 0; i < n; i++) {
					if (list[i] != subject) {
						if (best == 0) {
							best = list[i];
							bd = fcn_0050f980(subject->entity_index, best->entity_index, 1);
						} else {
							d = fcn_0050f980(subject->entity_index, list[i]->entity_index, 1);
							if (d < bd) {
								best = list[i];
								bd = d;
							}
						}
					}
				}
				if (best != 0) {
					if (n * 8.0f + 52.0f < bd) {
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
