




// SIZE 0x8
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/client_straftat.h"
typedef Pair_99f800 Pair;

// SIZE 0x21c
typedef struct {
	unsigned short id;
	unsigned char type;
	char pad3;
	int owner;
	char pad8[0x21c - 8];
} Obj;


extern Pair_99f800 cm_CrimeEvidenceLinks[0x800];
extern char gm_EntitySlotTable[];

char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl cm_SendRemoveStraftat(int id, int v);
void __cdecl he_NotifyStraftatExpired(char* o, char* p);

int __cdecl gs_ClearTargetStraftaten(int target, int max)
{
	int n;
	char* p;
	int flag[8];
	char* who[8];
	int m;
	int j;
	int k;
	int r;

	n = 0;
	p = gm_LookupEntityRecordById(target);
	m = 0;
	if (p != 0) {
		for (k = 0; k < 768 && m < 8; k++) {
			if ((((Obj*)gm_EntitySlotTable)[k].type == 6 || ((Obj*)gm_EntitySlotTable)[k].type == 7) && ((Obj*)gm_EntitySlotTable)[k].owner != target) {
				flag[m] = 0;
				who[m] = (char*) &((Obj*)gm_EntitySlotTable)[k];
				m++;
			}
		}
	}
	for (j = 0; j < 512 && n < max; j++) {
		if (cm_CrimeRecords[j].target_id == target && cm_CrimeRecords[j].state == 1) {
			for (k = 0; k < 2048; k++) {
				for (r = 0; r < m; r++) {
					if (cm_CrimeEvidenceLinks[k].owner == *(int*) (who[r] + 4) && cm_CrimeEvidenceLinks[k].key == cm_CrimeRecords[j].id) {
						flag[r] = 1;
					}
				}
			}
			cm_SendRemoveStraftat(cm_CrimeRecords[j].id, 1);
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
