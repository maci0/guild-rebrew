#include "Develop/DieGildeAddOn/game/event_callbacks.h"


#include "Develop/DieGildeAddOn/game/game_timestamp.h"






// SIZE 0xe


typedef struct {
	int id;
	int done;
	unsigned char type;
	char pad9[3];
	int key;
	char pad10[8];
	GAME_TIMESTAMP t;
	unsigned char flags;
	char pad27;
	int busy;
	char pad2c[4];
	char active;
	char pad31[0xe3];
} Ent;
// SIZE 0x114

typedef struct {
	EVENT_CHECK fn;
	char pad4[0x10];
} Kind;
// SIZE 0x14

#include "Develop/DieGildeAddOn/game/game_data.h"
extern char gm_EntityIdField[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int nt_NetSyncFlags;
extern unsigned char gm_ClientModeFlags;
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(GAME_TIMESTAMP *, int, int, int);
int __cdecl gm_CompareGameTime(GAME_TIMESTAMP *, GAME_TIMESTAMP *);
void __cdecl cm_RequestRemoveCutscene(int);
#include "Develop/DieGildeAddOn/game/cutscene.h"

/* ADDRESS: GOLDTL 0x004e6650 */
/* ADDRESS: GOLDDE 0x004d2ea0 */
int __cdecl cut_UpdateCutscenes(void)
{
	GAME_TIMESTAMP t;
	int i;
	int r;

	for (i = 0; i < 96; i++) {
		if (((Ent*)cut_Cutscenes)[i].active != 0 && (((Ent*)cut_Cutscenes)[i].flags & 5) == 0) {
			t = ((Ent*)cut_Cutscenes)[i].t;
			gm_AddTime(&t, 0, -60, 0);
			if (((Ent*)cut_Cutscenes)[i].key == -1 && ((nt_NetSyncFlags & 8) != 0 || ((*(int*)&gm_ClientModeFlags) & 8) != 0)) {
				((Ent*)cut_Cutscenes)[i].key = *(int *) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c);
			}
			if (*(int *) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c) == ((Ent*)cut_Cutscenes)[i].key && ((Ent*)cut_Cutscenes)[i].busy == 0 &&
			    gm_CompareGameTime(&(*(GAME_TIMESTAMP*)&gm_GameTime), &t) > 0) {
				r = cut_CutsceneReady((int*) &((Ent*)cut_Cutscenes)[i]);
				if (r == -1) {
					gm_AddTime(&((Ent*)cut_Cutscenes)[i].t, 0, 5, 0);
					if (((Ent*)cut_Cutscenes)[i].t.hour >= 22) {
						gm_AddTime(&((Ent*)cut_Cutscenes)[i].t, 9, 0, 0);
					}
					continue;
				}
				if (r == 0) {
					gm_AddTime(&((Ent*)cut_Cutscenes)[i].t, 0, 30, 0);
					if (((Ent*)cut_Cutscenes)[i].t.hour >= 22) {
						gm_AddTime(&((Ent*)cut_Cutscenes)[i].t, 9, 0, 0);
					}
					continue;
				}
				if (((Kind*) (he_EventCallbacks + 0x10))[((Ent*)cut_Cutscenes)[i].type].fn != 0 && ((Kind*) (he_EventCallbacks + 0x10))[((Ent*)cut_Cutscenes)[i].type].fn((char*) &((Ent*)cut_Cutscenes)[i]) == 0) {
					cm_RequestRemoveCutscene(((Ent*)cut_Cutscenes)[i].id);
					continue;
				}
			}
			if (((Kind*) (he_EventCallbacks + 0x10))[((Ent*)cut_Cutscenes)[i].type].fn == 0 && gm_CompareGameTime(&(*(GAME_TIMESTAMP*)&gm_GameTime), &((Ent*)cut_Cutscenes)[i].t) > 0) {
				((Ent*)cut_Cutscenes)[i].done = 1;
			}
			if (gm_CompareGameTime(&(*(GAME_TIMESTAMP*)&gm_GameTime), &((Ent*)cut_Cutscenes)[i].t) > 0 && ((Ent*)cut_Cutscenes)[i].done == 0) {
				if (cut_IsParticipant(*(int *) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c), (unsigned char*) &((Ent*)cut_Cutscenes)[i]) != 0 &&
				    (((Ent*)cut_Cutscenes)[i].flags & 0x80) != 0) {
					if (*(int *) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c + 0x208) == ((Ent*)cut_Cutscenes)[i].id) {
						((Ent*)cut_Cutscenes)[i].done = 1;
					}
				} else if (((Ent*)cut_Cutscenes)[i].key == *(int *) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c) &&
					   (((Ent*)cut_Cutscenes)[i].flags & 2) != 0) {
					((Ent*)cut_Cutscenes)[i].done = 1;
				} else {
					cut_FreeCutscene(((Ent*)cut_Cutscenes)[i].id);
				}
			}
			if (gm_CompareGameTime(&(*(GAME_TIMESTAMP*)&gm_GameTime), &t) > 0 && ((Ent*)cut_Cutscenes)[i].done != 0) {
				d2_InsideBuildingActive = 0;
				cut_ExecuteCutscene((int*) &((Ent*)cut_Cutscenes)[i]);
				cut_FreeCutscene(((Ent*)cut_Cutscenes)[i].id);
			}
		}
	}
	return 0;
}
unsigned char _dpad_9a9220[1088];
unsigned char _dpad_9a9660[26500];
