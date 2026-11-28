#include <stdlib.h>
#include <string.h>

typedef struct Query {
	int x0;
	int flags;
	char pad8[0x14 - 8];
	int kind;
	char pad18[0x1c - 0x18];
	char name[0x20];
	char pad3c[0x50 - 0x3c];
} Query;
// SIZE 0x50

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







extern int gm_RandomSearchSteps[];


unsigned short __cdecl gm_RandomMod(int);
int __cdecl gm_GetEntityOfficeRank(unsigned short, int);
int __cdecl gm_MatchesTargetFilter(unsigned short a, unsigned short b, Query* q, int c);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);


/* Collects up to max entities near e's level into out, walking the entity
 * table from a random start with a random stride: first those with a job
 * other than 0x52, then jobless ones. */
/* ADDRESS: GOLDTL 0x004a5960 */
/* ADDRESS: GOLDDE 0x00494360 */
unsigned int __cdecl gm_FindSimilarEntities(unsigned short* e, unsigned int max, int a2, float lo, float hi, unsigned short* out)
{
	Query q;
	int step;
	unsigned int cnt;
	int ranged;
	int tries;
	int i;
	float f;
	unsigned char t;
	unsigned char job;

	step = gm_RandomSearchSteps[gm_RandomMod(0x10)];
	ranged = 0;
	memset(&q, 0, sizeof(q));
	memset(q.name, 0xff, sizeof(q.name));
	if ((lo > 0.0 || hi < 100.0) && lo < hi) {
		ranged = 1;
	}
	q.kind = 2;
	q.flags = a2;
	a2 = gm_GetEntityOfficeRank(*e, 0);
	tries = 0x300;
	cnt = 0;
	i = gm_RandomMod(0x300);
	while (cnt < max && tries != 0) {
		t = ((ENTITY_RECORD*)gm_EntitySlotTable)[i].entity_state;
		if (t != 8 && t != 7 && t != 5 && t != 9 && t != 0x14) {
			job = ((ENTITY_RECORD*)gm_EntitySlotTable)[i].unk_164;
			if (job != 0 && job != 0x52 && gm_MatchesTargetFilter(*e, (unsigned short) i, &q, 0) != 0
			    && abs(a2 - gm_GetEntityOfficeRank((unsigned short) i, 0)) < 6) {
				if (!ranged || (f = gm_CalcEntityFavor(i, *e, 1), !(f < lo) && !(f > hi))) {
					out[cnt++] = (unsigned short) i;
				}
			}
		}
		tries--;
		i = (step + i) % 0x300;
	}
	tries = 0x300;
	i = gm_RandomMod(0x300);
	while (cnt < max && tries != 0) {
		t = ((ENTITY_RECORD*)gm_EntitySlotTable)[i].entity_state;
		if (t != 8 && t != 7 && t != 5 && t != 9 && t != 0x14) {
			if (((ENTITY_RECORD*)gm_EntitySlotTable)[i].unk_164 == 0 && gm_MatchesTargetFilter(*e, (unsigned short) i, &q, 0) != 0
			    && abs(a2 - gm_GetEntityOfficeRank((unsigned short) i, 0)) < 6) {
				if (!ranged || (f = gm_CalcEntityFavor(i, *e, 1), !(f < lo) && !(f > hi))) {
					out[cnt++] = (unsigned short) i;
				}
			}
		}
		tries--;
		i = (i + step) % 0x300;
	}
	return cnt;
}
