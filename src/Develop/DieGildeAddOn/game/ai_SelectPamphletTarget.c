


#include "Develop/DieGildeAddOn/game/entity_record.h"








unsigned short __cdecl gm_RandomMod(int n);
int __cdecl ai_SelectRankedCandidates(char* e, int a, int* b, float c, float r, int* out);
int __cdecl he_CountEntityActions(char* e, ENTITY_RECORD* t, int* cnt);
int __cdecl he_HasNoActiveAction0x88(ENTITY_RECORD* t, char* e);
double __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDDE 0x004989e0 */
int __cdecl ai_SelectPamphletTarget(char* actor, char* unused, char* out)
{
	int cnt;
	int mask;
	int idx;

	cnt = 0;
	if (*(int*) (actor + 0x194) < 1) {
		return 0;
	}
	mask = 0xf00500;
	if (ai_SelectRankedCandidates(actor, 1, &mask, 0, gm_RandomMod(0x40), &idx) == 0) {
		return 0;
	}
	if (he_CountEntityActions(actor, ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[(unsigned short) idx]), &cnt) == 0) {
		return 0;
	}
	if (he_HasNoActiveAction0x88(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[(unsigned short) idx]), actor) == 0) {
		return 0;
	}
	if (cnt > 3) {
		return 0;
	}
	if (gm_RandomFloat01() < cnt * 0.25f) {
		return 0;
	}
	out[0] = 7;
	*(int*) (out + 4) = ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[(unsigned short) idx].entity_id;
	return 1;
}
