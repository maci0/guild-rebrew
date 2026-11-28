




// SIZE 0x8
#include "Develop/client_types.h"
#include "Develop/DieGildeAddOn/game/client_straftat.h"
typedef Pair_99f800 Pair;

// SIZE 0x21c
typedef struct {
	char pad0[4];
	int owner;
	char pad8[0x21c - 8];
} Obj;


extern Pair_99f800 cm_CrimeEvidenceLinks[0x800];
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl FindStraftatIndexById(int key);
char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl cm_SubtractCrimeGrid(int arg, unsigned char kind);
void __cdecl he_NotifyStraftatExpired(Obj* o, char* p);

/* ADDRESS: GOLDDE 0x004e19b0 */
int __cdecl gs_RemoveStraftat(int key, int force)
{
	int idx;
	char* targetEntity;
	int i;

	idx = FindStraftatIndexById(key);
	if (idx == -1) {
		return 3;
	}
	if (cm_CrimeRecords[idx].count > 0) {
		cm_CrimeRecords[idx].count--;
	}
	if (cm_CrimeRecords[idx].count != 0 && force == 0) {
		return 2;
	}
	if (cm_CrimeRecords[idx].state != 1 && (force == 0 || cm_CrimeRecords[idx].state == 0)) {
		return 1;
	}
	targetEntity = gm_LookupEntityRecordById(cm_CrimeRecords[idx].target_id);
	cm_SubtractCrimeGrid(cm_CrimeRecords[idx].unk_21, cm_CrimeRecords[idx].kind);
	for (i = 0; i < 2048; i++) {
		if (key == cm_CrimeEvidenceLinks[i].key) {
			if (gm_LocalPlayerSlot != 0xffff && cm_CrimeEvidenceLinks[i].owner == (*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id) && targetEntity != 0 && force == 0) {
				he_NotifyStraftatExpired(((Obj*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot]), targetEntity);
			}
			cm_CrimeEvidenceLinks[i].owner = -1;
			cm_CrimeEvidenceLinks[i].key = -1;
		}
	}
	cm_CrimeRecords[idx].state = 0;
	cm_CrimeRecords[idx].target_id = -1;
	cm_CrimeRecords[idx].id = -1;
	return 0;
}
