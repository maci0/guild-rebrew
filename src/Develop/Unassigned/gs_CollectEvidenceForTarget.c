
#include "Develop/DieGildeAddOn/game/entity_record.h"

#include <string.h>

#include "client_types.h"
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

extern Rec2d_9a3800 g_9a3800[512];
extern Pair_99f800 g_99f800[0x800];
extern char g_7f4ca0[];

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
	holder = ((char*)&((ENTITY_RECORD*)g_7f4ca0)[holderSlot]);
	if (holder == 0) {
		return 0;
	}
	memset(outIds, 0xff, 0x20 * 4);
	for (i = 0; i < 0x800; i++) {
		if (((Pair*)g_99f800)[i].a == *(int*) (holder + 4)) {
			idx = FindStraftatIndexById(((Pair*)g_99f800)[i].b);
			if (idx != -1 && g_9a3800[idx].x16 == targetId) {
				outIds[count] = g_9a3800[idx].id;
				count++;
				if (count > 0x20) {
					break;
				}
			}
		}
	}
	return count;
}
