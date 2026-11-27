#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#pragma intrinsic(memset)
#include "Develop/DieGildeAddOn/game/entity_record.h"
/* SIZE 0x54 */
typedef struct {
	char pad0[0xc];
	int f0c;
	int armor[2];
	int weapon[6];
	int f30;
	int f34;
	int f38;
	int f3c;
	int f40;
	int f44;
	int f48;
	int f4c;
	int f50;
} BUILDING_BALANCE_INFO;

extern char* lpGebaeudePROT;
extern unsigned char g_773d75;
#include "Develop/DieGildeAddOn/game/game_data.h"

float __cdecl gm_GetWorkforceOutput(unsigned char* p, int k, int a, int b);
void* __cdecl ahm_GetWorkshopOwner(unsigned char* e);
int __cdecl ahm_CalcWorkshopOutputScore(char* e);
char* __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl gm_SumQueryEntryValues(int, unsigned char b);

/* ADDRESS: GOLDTL 0x0050c1b0 */
int __cdecl gm_CalcBuildingRoundBalance(unsigned char* bld, int ownerIdx, char* out)
{
	unsigned char* row;
	int slot;
	int k;
	ENTITY_RECORD* ent;
	char* entry;
	int var;
	int total;
	int sum;
	int found;
	int i;
	int val;

	total = 0;
	var = 0;
	sum = 0;
	memset(out, 0, 0x54);
	row = (unsigned char*)
	    ((char*) &((BUILDING_PROTOTYPE*) lpGebaeudePROT)[(unsigned int) *bld]);
	if (ownerIdx != *(unsigned short*) (bld + 0x27)) {
		goto tail;
	}
	slot = (int) &((ENTITY_RECORD*) g_7f4ca0)[ownerIdx];
	if (*row == 0x1e) {
		if (ahm_GetWorkshopOwner(bld) != 0) {
			val = ahm_CalcWorkshopOutputScore((char*) bld);
			*(int*) (out + 0x18) = val;
			total = val;
		}
		goto finalize;
	}
	for (k = 0; k < 0x300; k++) {
		ent = &((ENTITY_RECORD*) g_7f4ca0)[k];
		if (ent->unk_16c != (char*) bld) {
			continue;
		}
		found = 0;
		for (i = 0; i < 6; i++) {
			if (row[i + 0x223] != 0 && row[i + 0x223] == ent->unk_164 &&
			    ent->entity_state != 0x14) {
				val = (int) (gm_GetWorkforceOutput((unsigned char*) slot, *bld, i, -1) *
					     ((double) *(int*) (bld + 0x3d) * 0.01));
				*(int*) (out + 0x18 + i * 4) += val;
				total += val;
				found = 1;
			}
		}
		for (i = 0; i < 2; i++) {
			if (row[i + 0x22f] != 0 && row[i + 0x22f] == ent->unk_165[0] &&
			    ent->entity_state != 0x14) {
				val = (int) (gm_GetWorkforceOutput((unsigned char*) slot, *bld, -1, i) *
					     ((double) *(int*) (bld + 0x3d) * 0.01));
				*(int*) (out + 0x10 + i * 4) += val;
				total += val;
				found = 1;
			}
		}
		if (found == 0 && ent->entity_state != 0x14) {
			val = (int) (gm_GetWorkforceOutput((unsigned char*) slot, *bld, -1, 0) *
				     ((double) *(int*) (bld + 0x3d) * 0.01));
			*(int*) (out + 0x10) += val;
			total += val;
		}
	}
finalize:
	*(int*) (out + 0xc) = total;
	*(int*) (out + 0x48) = *(int*) (bld + 0x4d);
	sum += total;
	if (*row == 5) {
		*(int*) (out + 0x28) = *(int*) (bld + 0x55);
		var = *(int*) (bld + 0x55);
	}
	if (*row == 7) {
		entry = fcn_00502cd0(*(int*) (bld + 0x5d), 2, 6, 0, 0xe8);
		if (entry != 0) {
			val = gm_SumQueryEntryValues(*(int*) (entry + 0x14), g_773d75);
			*(int*) (out + 0x30) += val;
			var += *(int*) (out + 0x30);
		}
		entry = fcn_00502cd0(*(int*) (bld + 0x5d), 2, 6, 0, 0xf0);
		if (entry != 0) {
			val = gm_SumQueryEntryValues(*(int*) (entry + 0x14), g_773d75);
			*(int*) (out + 0x3c) += val;
			var += *(int*) (out + 0x3c);
		}
		*(int*) (out + 0x34) += *(int*) (bld + 0x65);
		*(int*) (out + 0x38) += *(int*) (bld + 0x69);
		var += *(int*) (out + 0x34) + *(int*) (out + 0x38);
	} else if (*row == 0x16) {
		val = *(int*) (bld + 0x6d);
		*(int*) (out + 0x4c) = val;
		var += val;
	}
tail:
	*(int*) (out + 0x40) = sum;
	*(int*) (out + 0x44) = var;
	*(int*) (out + 0x50) = var - sum;
	if (sum == 0 && var == 0) {
		return 0;
	}
	return 1;
}
