

#include <string.h>
#pragma intrinsic(memset)

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"








#define HOUSES 768


#include "Develop/DieGildeAddOn/game/game_player.h"
extern char* gm_CityEntity;
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl gm_FindNextFilteredEntity(void);
char* __cdecl gm_ResolveParentEntity(char*);
void __cdecl gm_EquipDuelist(char*, char);
void __cdecl gm_AddTime(char*, int, int, int);
int __cdecl fcn_004c5980(void* data);

void __cdecl d2_BroadcastCutscene0xa2(char* p)
{
	char msg[0x114];
	char* e;
	char* par;
	int i;
	int n;

	e = gm_StartFilteredEntitySearch(1, 5, 0x10);
	if (e == 0) {
		return;
	}
	do {
		if (*(short*) (e + 0x27) != *(short*) gm_CityEntity) {
			break;
		}
		gm_FindNextFilteredEntity();
	} while (1);
	par = gm_ResolveParentEntity(p);
	memset(msg, 0, sizeof(msg));
	msg[8] = 3;
	msg[0x26] = (char) 0xa2;
	*(int*) (msg + 0x14) = -1;
	msg[0x30] = 2;
	*(int*) (msg + 0xc) = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[g_774970].entity_id;
	*(int*) (msg + 0x34) = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (e + 0x27)].entity_id;
	*(int*) (msg + 0x38) = *(int*) (par + 4);
	msg[0x7c] = 9;
	for (i = 0; i < 16; i++) {
		((int*) (msg + 0xc0))[i] = -1;
		((int*) (msg + 0x80))[i] = -1;
	}
	for (i = 0; i < 3; i++) {
		if (p != 0 && i == 0) {
			((int*) (msg + 0x100))[i] = *(int*) (p + 2);
		}
		else {
			((int*) (msg + 0x100))[i] = -1;
		}
	}
	if (p[0x28] == 2) {
		gm_EquipDuelist(msg, 2);
		gm_EquipDuelist(msg, 1);
	}
	else {
		gm_EquipDuelist(msg, p[0x28]);
	}
	*(int*) (msg + 0x10c) = *(int*) (e + 1);
	n = 0;
	for (i = 0; i < HOUSES; i++) {
		if (n >= 4) {
			break;
		}
		if (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_index != 0xffff && (*(char**)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].ptr_16c) == e) {
			((int*) (msg + 0xc0))[n] = ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id;
			n++;
		}
	}
	*(int*) (msg + 0x18) = (*(int*)&gm_GameTime);
	*(int*) (msg + 0x1c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x20) = g_7f4c08;
	*(short*) (msg + 0x24) = g_7f4c0c;
	gm_AddTime(msg + 0x18, 0, 0xf, 0);
	fcn_004c5980(msg);
}
