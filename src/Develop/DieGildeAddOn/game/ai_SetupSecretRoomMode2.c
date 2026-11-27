#include "Develop/DieGildeAddOn/game/entity_record.h"







/* SIZE 0x21c */



unsigned short __cdecl gm_RandomMod(int n);
int __cdecl ai_SelectRankedCandidates(char* e, int a, int* b, int c, float r, int* out);
int __cdecl amt_GetRoleLevel(int k);
int __cdecl gm_SumQueryEntryValues(int a, char b);
int __cdecl gm_WalkEntityChain(unsigned short raw_idx);

/* ADDRESS: GOLDTL 0x0048ddd0 */
int __cdecl ai_SetupSecretRoomMode2(char* actor, char* thresholdOut, char* resultOut)
{
	int mask;
	ENTITY_RECORD* target;
	int n;
	int nv;
	int tot[3];
	int thr[3];
	int total;

	mask = 0xf00500;
	{
		int idx;
		if (ai_SelectRankedCandidates(actor, 1, &mask, 0, gm_RandomMod(0x20) + 32.0f, &idx) == 0) {
			return 0;
		}
		target = ((ENTITY_RECORD *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[(unsigned short) idx]);
	}
	n = amt_GetRoleLevel(target->unk_165[1]) / 3 + 2;
	thr[0] = (int) (float) n;
	thr[1] = (int) ((float) n * 1.5f);
	thr[2] = (int) ((float) n * 2);
	if (*(int*) (actor + 0x194) >= thr[2]) {
		n = 2;
	} else if (*(int*) (actor + 0x194) >= thr[1]) {
		n = 1;
	} else if (*(int*) (actor + 0x194) >= thr[0]) {
		n = 0;
	} else {
		return 0;
	}
	gm_SumQueryEntryValues(*(int*) (actor + 0x178), *(char*) 0x773d75);
	total = gm_WalkEntityChain(*(unsigned short*) actor);
	total += gm_WalkEntityChain(target->entity_index);
	tot[0] = (int) ((float) total * *(float*) 0x662910);
	tot[1] = (int) ((float) total * *(float*) 0x664150);
	tot[2] = (int) ((float) total * *(float*) 0x6628ac);
	if (total >= thr[2]) {
		nv = 2;
	} else if (total >= thr[1]) {
		nv = 1;
	} else if (total >= thr[0]) {
		nv = 0;
	} else {
		return 0;
	}
	if (nv >= n) {
		nv = n;
	}
	*(int*) (resultOut + 8) = tot[nv];
	*(int*) (thresholdOut + 8) = thr[nv];
	*(int*) (resultOut + 0xc) = target->entity_id;
	*(int*) (resultOut + 0x10) = nv;
	*(int*) (thresholdOut + 0x10) = 2;
	return 1;
}
