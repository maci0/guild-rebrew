typedef struct Ent {
	unsigned short id;
	char pad2[0x164];
	unsigned char x166;
	unsigned char x167;
	unsigned char x168;
	char pad169[0x21c - 0x169];
} Ent;
// SIZE 0x21c

typedef struct Rec18 {
	char pad0[8];
	unsigned char x8;
	char pad9[0xf];
} Rec18;
// SIZE 0x18

extern char g_7f4ca0[];

int __cdecl fcn_004e8b40(int idx, Rec18* out);
#include "Develop/DieGildeAddOn/game/aemter.h"
int __cdecl fcn_004e9310(int k, int max, Ent** out);
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl fcn_004a5340(Ent* e, int a, int* b, int c, float r, int* out);

/* ADDRESS: GOLDTL 0x0049fc80 */
Ent* __cdecl fcn_0049fc80(Ent* subject)
{
	Ent* list[5];
	Rec18 q;
	Rec18 r;
	Ent* best;
	Ent* candidate;
	float d;
	int i;

	best = 0;
	if (subject->x166 == 0) {
		float bd;

		fcn_004e8b40(subject->x167, &q);
		for (i = 0; i < 768; i++) {
			candidate = &((Ent*)g_7f4ca0)[i];
			if (candidate->x166 != 0 && srv_GetEntityOfficeSlot((unsigned char*) candidate, &q, &r) != 0 && q.x8 <= 1) {
				if (best == 0) {
					best = candidate;
					bd = fcn_0050f980(subject->id, candidate->id, 1);
				} else {
					d = fcn_0050f980(subject->id, candidate->id, 1);
					if (d < bd) {
						bd = d;
						best = candidate;
					}
				}
			}
		}
	} else {
		if (subject->x168 != 0) {
			int n;
			float bd;

			n = fcn_004e9310(subject->x168, 5, list);
			if (n != 0) {
				for (i = 0; i < n; i++) {
					if (list[i] != subject) {
						if (best == 0) {
							best = list[i];
							bd = fcn_0050f980(subject->id, best->id, 1);
						} else {
							d = fcn_0050f980(subject->id, list[i]->id, 1);
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
				return &((Ent*)g_7f4ca0)[(unsigned short) idx];
			}
		}
	}
	return best;
}
