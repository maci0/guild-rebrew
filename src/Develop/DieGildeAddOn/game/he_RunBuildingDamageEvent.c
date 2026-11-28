#include "Develop/DieGildeAddOn/game/spiel.h"


// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"









unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, unsigned short);
unsigned char* __cdecl gm_AddObjekt(void);
unsigned char* __cdecl gm_FindNextFilteredEntity(void);

unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_AdjustGebaeudeCondition(unsigned char*, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, int, char*);
void __cdecl he_FreeAction(char*);

void __cdecl he_RunBuildingDamageEvent(char* u)
{
	unsigned char* cand[16];
	char text[0x418];
	unsigned char* e;
	int n;

	n = 0;
	if (*(int*) (u + 0x70) != -2) {
		if (*(int*) (u + 0x70) != 0) {
			return;
		}
		for (e = gm_StartFilteredEntitySearch(1, 4, *(unsigned short*) (u + 8)); e != 0 && n < 16; e = gm_FindNextFilteredEntity()) {
			if (gm_GetBuildingTypeCategory(*e) == 6) {
				cand[n++] = e;
			}
		}
		if (n != 0) {
			e = cand[gm_RandomMod(n)];
			if (e != 0) {
				gm_AdjustGebaeudeCondition(e, -0x32);
			}
			if (((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (u + 8)].entity_state == 6) {
				io_FormatTextBuffer(text, 0x10b8, e);
				he_MessageBoxQuickjump(((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (u + 8)].entity_id, ((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (u + 8)].entity_id, text, 0,
				    0x5ec, *(int*) (e + 1), -1, 0, 0);
			}
		}
	}
	he_FreeAction(u);
}
