
#include "Develop/DieGildeAddOn/game/entity_record.h"

#include <string.h>

#include "Develop/client_types.h"
#pragma pack(push, 1)
typedef Rec2d_9a3800 Rec2d;
// SIZE 0x2d
#pragma pack(pop)

typedef struct
{
	int a;
	int b;
} Pair;
// SIZE 0x8

extern Rec2d_9a3800 cm_CrimeRecords[512];
extern Pair_99f800 cm_CrimeEvidenceLinks[0x800];
extern char gm_EntitySlotTable[];

void* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl FindStraftatIndexById(int b);

int __cdecl gs_CollectEvidenceForTarget(int targetId, int* outIds, unsigned short holderSlot)
{
	char* holder;
	int count;
	int i;
	int idx;

	count = 0;
	if (gm_LookupEntityRecordById(targetId) == 0) {
		return 0;
	}
	holder = ((char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[holderSlot]);
	if (holder == 0) {
		return 0;
	}
	memset(outIds, 0xff, 0x20 * 4);
	for (i = 0; i < 0x800; i++) {
		if (((Pair*)cm_CrimeEvidenceLinks)[i].a == *(int*) (holder + 4)) {
			idx = FindStraftatIndexById(((Pair*)cm_CrimeEvidenceLinks)[i].b);
			if (idx != -1 && cm_CrimeRecords[idx].x16 == targetId) {
				outIds[count] = cm_CrimeRecords[idx].id;
				count++;
				if (count > 0x20) {
					break;
				}
			}
		}
	}
	return count;
}
