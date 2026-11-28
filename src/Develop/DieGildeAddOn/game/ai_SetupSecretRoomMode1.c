
#include "Develop/DieGildeAddOn/game/entity_record.h"

#include "entity_record.h"









#include "Develop/DieGildeAddOn/game/game_data.h"

unsigned short __cdecl gm_RandomMod(int n);
int __cdecl ai_SelectRankedCandidates(char* e, int a, int* b, int c, float r, int* out);
int __cdecl amt_GetRoleLevel(int k);

/* ADDRESS: GOLDDE 0x0047cba0 */
int __cdecl ai_SetupSecretRoomMode1(char* e, char* action, char* target)
{
	int mask;
	int idx;
	int thr[3];
	ENTITY_RECORD* t;
	int n;
	int k;

	mask = 0xf00500;
	if (ai_SelectRankedCandidates(e, 1, &mask, 0, gm_RandomMod(0x20) + 25.0f, &idx) == 0) {
		return 0;
	}
	t = ((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[(unsigned short) idx]);
	n = amt_GetRoleLevel(t->unk_165[1]) / 3 + 2;
	thr[0] = n + 3;
	thr[1] = n + 5;
	thr[2] = n + 8;
	if (*(int*) (e + 0x194) >= thr[2]) {
		k = 2;
	} else if (*(int*) (e + 0x194) >= thr[1]) {
		k = 1;
	} else if (*(int*) (e + 0x194) >= thr[0]) {
		k = 0;
	} else {
		return 0;
	}
	*(int*) (action + 8) = thr[k];
	*(int*) (target + 0xc) = t->entity_id;
	*(int*) (target + 0x10) = k;
	*(int*) (action + 0x10) = 1;
	return 1;
}
