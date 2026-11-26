


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


extern char* g_77261c;
extern unsigned int g_7728bc;

int __cdecl fcn_005cf720(unsigned short a, unsigned short b, Query* q, int c);
ENTITY_CANDIDATE* __cdecl fcn_004a34d0(void);

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
	if (((unsigned short*)g_77261c) != 0 && !(query.flags & 0x10000000)) {
		query.x40 = 0;
		query.flags = queryFlags;
		if (fcn_005cf720(*actor, *((unsigned short*)g_77261c), &query, 0) != 0) {
			*outId = *((unsigned short*)g_77261c);
			return 1;
		}
	}
	query.x40 = 0;
	for (i = (*(int*)&g_7728bc); candidate = fcn_004a34d0(), i != 0 && candidate->entity != 0; i--) {
		if (!(candidate->score < minScore) && !(candidate->score > maxScore) && fcn_005cf720(*actor, *(unsigned short*)candidate->entity, &query, 0) != 0) {
			*outId = *(unsigned short*)candidate->entity;
			return 1;
		}
	}
	return 0;
}
