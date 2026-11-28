#include <string.h>
#include "Develop/DieGildeAddOn/game/entity_candidate.h"

typedef struct Query {
	int x0;
	int flags;
	char pad8[0x14 - 8];
	int kind;
	char pad18[0x1c - 0x18];
	unsigned short name[0x10];
	char pad3c[0x40 - 0x3c];
	int x40;
	char pad44[0x50 - 0x44];
} Query;
/* SIZE 0x50 */


extern char* ai_FeudTargetEntity;
extern unsigned int gm_EntityCandidateCount;

int __cdecl gm_MatchesTargetFilter(unsigned short, unsigned short, Query*, int);
ENTITY_CANDIDATE* __cdecl gm_StepEntityCandidateRing(void);

/* ADDRESS: GOLD 0x004a58d0 */
/* ADDRESS: GOLDTL 0x004a5340 */
/* ADDRESS: GOLDDE 0x00493d40 */
int __cdecl ai_SelectRankedCandidates(unsigned short* e, unsigned int n, unsigned int* ids,
	float lo, float hi, unsigned short* out)
{
	Query q;
	int k;
	int found;
	int i;
	int j;
	ENTITY_CANDIDATE* t;

	if (n > 3) {
		return 0;
	}
	memset(&q, 0, sizeof(q));
	for (j = 0; j < 0x10; j++) {
		q.name[j] = 0xffff;
	}
	k = 0;
	q.kind = 2;
	if (ai_FeudTargetEntity != 0 && !(q.flags & 0x10000000)) {
		q.x40 = 0;
		q.flags = *ids;
		if (gm_MatchesTargetFilter(*e, *((unsigned short*) ai_FeudTargetEntity), &q, 0) != 0) {
			*out = *((unsigned short*) ai_FeudTargetEntity);
			k = 1;
		}
	}
	for (; k < n; k++) {
		q.flags = ids[k];
		if (k != 0) {
			q.name[k] = out[k - 1];
		} else {
			q.name[0] = *e;
		}
		found = 0;
		i = *(int*) &gm_EntityCandidateCount;
		t = gm_StepEntityCandidateRing();
		while (i != 0) {
			if (t->entity == 0) {
				return 0;
			}
			if (!(t->score < lo) && !(t->score > hi)
			    && gm_MatchesTargetFilter(*e, *(unsigned short*)t->entity, &q, 0) != 0) {
				out[k] = *(unsigned short*)t->entity;
				found = 1;
			}
			i--;
			t = gm_StepEntityCandidateRing();
			if (!found) {
				continue;
			}
			break;
		}
		if (!found) {
			return 0;
		}
	}
	return 1;
}
