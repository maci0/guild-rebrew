#include "Develop/DieGildeAddOn/game/entity_candidate.h"

typedef struct {
	ENTITY_CANDIDATE* cur;
	int step;
} fcn_004a34d0_ring;

extern unsigned int g_7728bc;
extern fcn_004a34d0_ring* g_664448;


/* ADDRESS: GOLDTL 0x004a34d0 */
ENTITY_CANDIDATE* __cdecl gm_StepEntityCandidateRing(void)
{
	unsigned int n;
	fcn_004a34d0_ring* r;
	ENTITY_CANDIDATE* cur;

	n = g_7728bc;
	r = g_664448;
	cur = r->cur;
	if (n == 0)
		return g_10082a0;
	r->cur = &g_10082a0[(cur - g_10082a0 + r->step) % n];
	return cur;
}
