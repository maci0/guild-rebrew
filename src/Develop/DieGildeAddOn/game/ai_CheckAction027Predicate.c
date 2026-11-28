#include "entity_record.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"








unsigned short __cdecl gm_RandomMod(int n);
int __cdecl ai_SelectRankedCandidates(char* e, int n, int* lim, float a4, float r, unsigned short* ids);

/* ADDRESS: GOLDTL 0x004a8e40 */
int __cdecl ai_CheckAction027Predicate(int unused1, char* e, int unused3, int unused4, char* out)
{
	int lim;
	unsigned short id;

	if (*(int*) (e + 0x194) < 3) {
		return 0;
	}
	lim = 0xf00500;
	if (!ai_SelectRankedCandidates(e, 1, &lim, 0.0f, (float) gm_RandomMod(0x12) + 32.0f, &id)) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[id].entity_id;
	return 1;
}
