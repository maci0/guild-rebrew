


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"





#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned short gm_GameTimeHour;

extern int g_7747f0;
extern char gm_InWorldHud;
extern char* gm_MarketEntity;
extern char str_empty[];

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
unsigned short __cdecl gm_RandomMod(int);
char* __cdecl gm_FindBuildingPrimarySlot(char*);
char* __cdecl gm_SetupEntityQuery(char*);
void __cdecl d2_EnterBuildingObjekt(char*, int, char*);
void __cdecl he_FreeAction(char*);

/* ADDRESS: GOLDDE 0x00556370 */
void __cdecl he_RunEvent0x85(char* u)
{
	char* list[0x40];
	int n;
	char* e;
	char* p;

	n = 0;
	if (g_7747f0 == 0) {
		*(int*) (u + 0x70) = -1;
	}
	switch (*(int*) (u + 0x70)) {
	case 0:
		if (gm_InWorldHud != 0) {
			((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (u + 8)].entity_type = 5;
			(*(int*) (u + 0x70))++;
		}
		break;
	case 1:
		if (gm_GameTimeHour >= 0x16) {
			(*(int*) (u + 0x70))++;
			break;
		}
		for (e = gm_StartFilteredEntitySearch(1, 4, *(unsigned short*) (u + 8)); e != 0 && n < 0x40; e = gm_FindNextFilteredEntity()) {
			list[n++] = e;
		}
		list[n++] = gm_MarketEntity;
		if (n != 0) {
			p = list[gm_RandomMod(n)];
			if (gm_RandomMod(4) != 0 && p != gm_MarketEntity && ((e = gm_FindBuildingPrimarySlot(p)) != 0 || (e = gm_SetupEntityQuery(p)) != 0)) {
				d2_EnterBuildingObjekt(p, *(int*) (e + 2), str_empty);
			} else {
				d2_EnterBuildingObjekt(p, -1, str_empty);
			}
		}
		*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
		*(short*) (u + 0x56) += gm_RandomMod(2);
		*(int*) (u + 0x58) = gm_RandomMod(0x3c);
		break;
	case 2:
		((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[*(unsigned short*) (u + 8)].entity_type = 6;
	case -2:
	case -1:
		he_FreeAction(u);
		break;
	}
}
