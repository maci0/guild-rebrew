#include "entity_record.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"








unsigned short __cdecl gm_RandomMod(int n);
int __cdecl ai_SelectRankedCandidates(char* e, int n, int* lim, float a4, float r, unsigned short* ids);
int __cdecl he_HasNoActiveEvent04b(char* e, ENTITY_RECORD* t);

/* ADDRESS: GOLDTL 0x004a9540 */
int __cdecl ai_PreparePrivFurchtEinfloessen(int unused1, char* actor, int unused3, int unused4, char* out)
{
	int filterMask;
	unsigned short targetId;

	if (*(int*) (actor + 0x194) < 2) {
		return 0;
	}
	filterMask = 0xf00500;
	if (!ai_SelectRankedCandidates(actor, 1, &filterMask, 0.0f, (float) gm_RandomMod(0x20) + 40.0f, &targetId)) {
		return 0;
	}
	if (!he_HasNoActiveEvent04b(actor, ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[targetId]))) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[targetId].entity_id;
	return 1;
}
