


#include <string.h>
#pragma intrinsic(memset)




// SIZE 0xe

typedef struct {
	int pad0;
	int f4;
	char pad8[0x180];
	char active;
	char pad189[0x93];
} ENTITY_SLOT_VIEW;
// SIZE 0x21c

typedef struct {
	char* name;
	int pad;
} OBJEKT_NAME_ENTRY;
// SIZE 0x8

#include "Develop/DieGildeAddOn/game/entity_record.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char* d2_HoveredSceneObject;
extern int g_7746f0;
extern int gm_AllEntitiesControllable;
extern int g_14ce8cc;
extern char* g_14a555c;
extern char* g_14a5558;
extern int g_14a79c0[];

char* __cdecl plt_FindRecordByOwner(int, int);
void __cdecl cm_SendCopyEntityData(char*);
void __cdecl cm_ExProdObjekt(void);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl d2_SetMouseTooltip(char*);

void __cdecl d2_HandleErnten(char* building, int plant_table)
{
	char* entry;
	int i;

	if ((*(int*)&d2_HoveredSceneObject) == 0) {
		return;
	}
	entry = plt_FindRecordByOwner(plant_table, (*(int*)&d2_HoveredSceneObject));
	if (g_7746f0 != 0) {
		if (entry == 0) {
			return;
		}
		if ((entry[0xd] > 1 || gm_AllEntitiesControllable != 0) && g_14ce8cc != 0) {
			for (i = 0; i < 768; i++) {
				if ((*(char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].selected)) {
					char msg[0xf8];

					memset(msg, 0, sizeof(msg));
					*(int*) (msg + 8) = (*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[gm_LocalPlayerSlot].entity_id);
					msg[4] = 0x28;
					*(int*) (msg + 0x10) = 1;
					*(int*) (msg + 0x14) = 0;
					msg[0x36] = 1;
					*(int*) (msg + 0xc) = *(int*) (building + 1);
					*(pos14_7f4c00*) (msg + 0x28) = gm_GameTime;
					*(int*) (msg + 0x64) = *(int*) entry;
					*(int*) (msg + 0x5c) = (*(int*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_id);
					*(int*) (msg + 0x58) = *(int*) (building + 1);
					cm_SendCopyEntityData(msg);
					cm_ExProdObjekt();
				}
			}
			return;
		}
	}
	if (entry == 0) {
		return;
	}
	if (entry[0xd] > 1) {
		char text[0xf8];

		fcn_0064d41a(text, g_14a555c, ((OBJEKT_NAME_ENTRY*)g_14a79c0)[*(unsigned short*) (entry + 0xa)].name);
		d2_SetMouseTooltip(text);
	} else {
		d2_SetMouseTooltip(g_14a5558);
	}
}
