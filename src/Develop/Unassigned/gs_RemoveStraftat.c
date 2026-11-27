




// SIZE 0x8
#include "client_types.h"
#include "client_straftat.h"
typedef Pair_99f800 Pair;

// SIZE 0x21c
typedef struct {
	char pad0[4];
	int owner;
	char pad8[0x21c - 8];
} Obj;


extern Pair_99f800 g_99f800[0x800];
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"

int __cdecl FindStraftatIndexById(int key);
char* __cdecl gm_LookupEntityRecordById(int id);
void __cdecl cm_SubtractCrimeGrid(int arg, unsigned char kind);
void __cdecl he_NotifyStraftatExpired(Obj* o, char* p);

int __cdecl gs_RemoveStraftat(int key, int force)
{
	int idx;
	char* targetEntity;
	int i;

	idx = FindStraftatIndexById(key);
	if (idx == -1) {
		return 3;
	}
	if (g_9a3800[idx].count > 0) {
		g_9a3800[idx].count--;
	}
	if (g_9a3800[idx].count != 0 && force == 0) {
		return 2;
	}
	if (g_9a3800[idx].state != 1 && (force == 0 || g_9a3800[idx].state == 0)) {
		return 1;
	}
	targetEntity = gm_LookupEntityRecordById(g_9a3800[idx].target_id);
	cm_SubtractCrimeGrid(g_9a3800[idx].unk_21, g_9a3800[idx].kind);
	for (i = 0; i < 2048; i++) {
		if (key == g_99f800[i].key) {
			if (g_774970 != 0xffff && g_99f800[i].owner == (*(int*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id) && targetEntity != 0 && force == 0) {
				he_NotifyStraftatExpired(((Obj*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970]), targetEntity);
			}
			g_99f800[i].owner = -1;
			g_99f800[i].key = -1;
		}
	}
	g_9a3800[idx].state = 0;
	g_9a3800[idx].target_id = -1;
	g_9a3800[idx].id = -1;
	return 0;
}
