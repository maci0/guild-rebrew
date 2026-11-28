


#pragma pack(1)
// SIZE 0x2d
typedef struct {
	int id;
	char pad4[0x2d - 4];
} Order;
#pragma pack()

// SIZE 0x8
#include "Develop/client_types.h"
typedef Pair_99f800 Pair;

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x21c - 8];
} Obj;

extern Rec2d_9a3800 cm_CrimeRecords[512];
extern Pair_99f800 cm_CrimeEvidenceLinks[0x800];
#include "Develop/DieGildeAddOn/game/entity_record.h"

char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl cm_SendRemoveStraftat(int id, int v);
void __cdecl he_NotifyStraftatExpired(char* o, char* p);

int __cdecl gs_ClearStraftatenByIds(int target, int count, int* ids)
{
	int n;
	int flag[8];
	char* who[8];
	char* p;
	int m;
	int i;
	int j;
	int k;
	int r;
	int id;
	int found;

	n = 0;
	p = gm_LookupEntityRecordById(target);
	m = 0;
	if (p != 0) {
		for (k = 0; k < 768 && m < 8; k++) {
			if ((((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[k].entity_type == 6 || ((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[k].entity_type == 7) &&
				((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[k].entity_id != target) {
				flag[m] = 0;
				who[m] = (char*) ((Obj*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[k]);
				m++;
			}
		}
	}
	for (i = 0; i < count; i++) {
		id = ids[i];
		found = 0;
		for (j = 0; j < 512; j++) {
			if (((Order*)cm_CrimeRecords)[j].id == id) {
				found = 1;
				break;
			}
		}
		if (found) {
			for (k = 0; k < 2048; k++) {
				for (r = 0; r < m; r++) {
					if (cm_CrimeEvidenceLinks[k].owner == *(int*) (who[r] + 4) && cm_CrimeEvidenceLinks[k].key == id) {
						flag[r] = 1;
					}
				}
			}
			cm_SendRemoveStraftat(id, 1);
			n++;
		}
	}
	for (r = 0; r < m; r++) {
		if (flag[r] != 0) {
			he_NotifyStraftatExpired(who[r], p);
		}
	}
	return n;
}
