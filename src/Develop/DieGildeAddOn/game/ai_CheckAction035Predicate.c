


#include <string.h>

unsigned short __cdecl gm_RandomMod(int n);
#include "Develop/DieGildeAddOn/game/aemter.h"
char* __cdecl gm_LookupEntityRecordById(int id);
float __cdecl gm_CalcEntityFavor(unsigned int a0, unsigned int a1, unsigned int a2);

int __cdecl ai_CheckAction035Predicate(char* unused, char* entity, char* ctx, char* unused2, char* out)
{
	int id;
	float score;
	char* cands[6];
	OFFICE_SLOT recs[6];
	int n;
	int i;
	int k;
	int tries;
	char* c;

	if (*(int*) (entity + 0x1c8) & 0x100) {
		return 0x20;
	}
	if (*(int*) (entity + 0x194) < 4) {
		return 0x20;
	}
	if (*(int*) ctx == 1) {
		id = *(int*) (entity + 4);
	} else if (*(int*) ctx == 2 && *(char**) (ctx + 0x21c) != 0) {
		id = *(int*) (*(char**) (ctx + 0x21c) + 4);
	} else {
		return 0;
	}
	n = amt_FindOfficeSlotsByKind(4, 6, recs);
	for (i = 0; i < n; i++) {
		cands[i] = gm_LookupEntityRecordById(recs[i].mplayerid);
	}
	for (i = n; i < 6; i++) {
		cands[i] = 0;
	}
	k = gm_RandomMod(6);
	for (tries = 6; tries != 0;) {
		c = cands[k];
		if (c != 0 && id != *(int*) (c + 4)) {
			score = gm_CalcEntityFavor(*(unsigned short*) c, *(unsigned short*) entity, 1);
			if (gm_RandomMod(0x10) + 16.0f > score) {
				c = cands[k];
				if (c == 0 || *(int*) (entity + 0x5c) == *(int*) (c + 4)) {
					return 0;
				}
				out[0] = 7;
				*(int*) (out + 4) = *(int*) (c + 4);
				return 1;
			}
		}
		tries--;
		k = (k + 1) % 6;
	}
	return 0;
}
