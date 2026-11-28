#include "entity_record.h"









unsigned short __cdecl gm_RandomMod(int n);
int __cdecl ai_SelectRankedCandidates(int a, int n, int* lim, int a4, float r, unsigned short* ids);

/* ADDRESS: GOLDTL 0x004a8da0 */
/* ADDRESS: GOLDDE 0x004970e0 */
int __cdecl ai_CheckAction025Predicate(int unused1, int actor, int unused3, int unused4, char* out)
{
	unsigned short ids[2];
	int lim[2];

	lim[0] = 0xf00500;
	lim[1] = 0xf00500;
	if (!ai_SelectRankedCandidates(actor, 2, lim, 0, (float) gm_RandomMod(0x40), ids)) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = ((ENTITY_RECORD*)gm_EntitySlotTable)[ids[0]].entity_id;
	*(int*) (out + 8) = ((ENTITY_RECORD*)gm_EntitySlotTable)[ids[1]].entity_id;
	return 1;
}
