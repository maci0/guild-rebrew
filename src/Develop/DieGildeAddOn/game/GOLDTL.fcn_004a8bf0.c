


#include "Develop/DieGildeAddOn/game/entity_record.h"








unsigned short __cdecl gm_RandomMod(int n);
int __cdecl ai_SelectRankedCandidates(char* e, int a, int* b, int c, float r, int* out);

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

int __cdecl ai_CheckAction01cPredicate(char* unused1, char* actor, char* ctx, char* unused4, char* out)
{
	int mask;
	int idx;

	if (*(int*) (actor + 0x194) < 3) {
		return 0;
	}
	mask = actor[9] ? 0xf00501 : 0xf00502;
	if (ai_SelectRankedCandidates(actor, 1, &mask, 0, gm_RandomMod(0x40), &idx) == 0) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[(unsigned short) idx].entity_id;
	*(int*) (out + 8) = min(max(gm_RandomMod(*(int*) (actor + 0x194) / 2), 1), 5);
	return 1;
}
