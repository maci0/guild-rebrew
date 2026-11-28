


#include <string.h>
#include "Develop/DieGildeAddOn/game/entity_candidate.h"

typedef struct Query {
	int x0;
	int flags;
	char pad8[0x14 - 8];
	int kind;
	char pad18[0x1c - 0x18];
	char name[0x20];
	char pad3c[0x40 - 0x3c];
	int x40;
	char pad44[0x50 - 0x44];
} Query;
// SIZE 0x50


extern char* ai_FeudTargetEntity;
extern unsigned int gm_EntityCandidateCount;

int __cdecl gm_MatchesTargetFilter(unsigned short a, unsigned short b, Query* q, int c);
ENTITY_CANDIDATE* __cdecl gm_StepEntityCandidateRing(void);

int __cdecl gm_FindEntityCandidate(unsigned short* actor, int queryFlags, unsigned int excludedCount, char* excludedIds, float minScore, float maxScore, unsigned short* outId)
{
	Query query;
	unsigned int len;
	int i;
	ENTITY_CANDIDATE* candidate;

	memset(&query, 0, sizeof(query));
	len = excludedCount * 2;
	if (len > 0x20) {
		len = 0x20;
	}
	memcpy(query.name, excludedIds, len);
	query.kind = 2;
	if (((unsigned short*)ai_FeudTargetEntity) != 0 && !(query.flags & 0x10000000)) {
		query.x40 = 0;
		query.flags = queryFlags;
		if (gm_MatchesTargetFilter(*actor, *((unsigned short*)ai_FeudTargetEntity), &query, 0) != 0) {
			*outId = *((unsigned short*)ai_FeudTargetEntity);
			return 1;
		}
	}
	query.x40 = 0;
	for (i = (*(int*)&gm_EntityCandidateCount); candidate = gm_StepEntityCandidateRing(), i != 0 && candidate->entity != 0; i--) {
		if (!(candidate->score < minScore) && !(candidate->score > maxScore) && gm_MatchesTargetFilter(*actor, *(unsigned short*)candidate->entity, &query, 0) != 0) {
			*outId = *(unsigned short*)candidate->entity;
			return 1;
		}
	}
	return 0;
}
