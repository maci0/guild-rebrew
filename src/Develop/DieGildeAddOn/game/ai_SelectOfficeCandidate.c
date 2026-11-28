int __cdecl amt_FindOfficeSlotByKey(int, void*);
char* __cdecl gm_LookupEntityRecordById(int);
#include "Develop/DieGildeAddOn/game/aemter.h"
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);
int __cdecl gm_HasActiveSpecialObject(void*, int);
unsigned short __cdecl gm_RandomMod(unsigned short);

struct OFFICE_SLOT_INFO {
	int pad0[2];
	unsigned char kind;
	char pad9[15];
};
// SIZE 0x18


/* ADDRESS: GOLDTL 0x004aae50 */
/* ADDRESS: GOLDDE 0x00499190 */
int __cdecl ai_SelectOfficeCandidate(int officeKey, unsigned short* referenceId, int* candidateIds, int* unusedOut)
{
	float score[4];
	char* candidates[4];
	struct OFFICE_SLOT_INFO info;
	float bonus;
	float best;
	char* candidate;
	int i;
	int tie;
	int idx;
	int k;

	*unusedOut = 0;
	if (amt_FindOfficeSlotByKey(officeKey, &info) == 0)
		return -1;
	for (i = 0; i < 4; i++) {
		candidate = gm_LookupEntityRecordById(candidateIds[i]);
		candidates[i] = candidate;
		if (candidate != 0 && amt_GetOfficeAffinity((unsigned char*) candidate, info.kind, &bonus) != 0) {
			score[i] = gm_CalcEntityFavor(*(unsigned short*) candidate, *referenceId, 1) + bonus;
			if (gm_HasActiveSpecialObject(candidate, 0x2be) != 0)
				score[i] += 0.2f;
			if ((*(int*) (candidate + 0x1cc) & 0x400000) != 0)
				score[i] -= 0.2f;
		} else {
			score[i] = -1000.0f;
		}
	}
	best = -10.0f;
	tie = 0;
	idx = -1;
	for (i = 0; i < 4; i++) {
		if (candidates[i] != 0 && score[i] > best) {
			best = score[i];
			tie = 0;
			idx = i;
		} else if (candidates[i] != 0 && score[i] == best) {
			tie = 1;
		}
	}
	if (idx < 0)
		return -1;
	if (tie == 0)
		return *(int*) (candidates[idx] + 4);
	idx = -1;
	i = gm_RandomMod(4);
	for (k = 4; k != 0; k--, i = (i + 1) % 4) {
		if (score[i] == best && candidates[i] != 0) {
			idx = i;
			break;
		}
	}
	if (idx < 0)
		return -1;
	return *(int*) (candidates[idx] + 4);
}
