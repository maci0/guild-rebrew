#include "Develop/DieGildeAddOn/game/building_prototype.h"


// SIZE 0x6c4
typedef struct {
	int key;
	char names[16][48];
	char pad304[0x6c4 - 0x304];
} NameSet;

// SIZE 0x21c
typedef struct {
	char pad0[0x16c];
	unsigned char* home;
	char pad170[0x184 - 0x170];
	char* view;
	char pad188[0x21c - 0x188];
} Obj;

extern NameSet g_699b18[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
extern unsigned char* lpGebaeudePROT;

void __cdecl ch_CollectContextCharacters(unsigned char* home);
void __cdecl ch_PreloadCharacterMotions(char* view, int n, ...);

/* ADDRESS: GOLDDE 0x00501110 */
void __cdecl ch_PreloadBuildingMotions(unsigned char* home)
{
	NameSet* s;
	int k;
	unsigned char* rec;
	int i;

	rec = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*home];
	for (k = 0; g_699b18[k].key != 0; k++) {
		if (g_699b18[k].key == (((BUILDING_PROTOTYPE*)rec)->category)) {
			break;
		}
	}
	s = &g_699b18[k];
	ch_CollectContextCharacters(home);
	for (i = 0; i < 768; i++) {
		if ((*(char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_184) != 0 &&
		    ((*(unsigned char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_16c) == home || *(int*) ((*(char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_184) + 0x2c) == *(int*) (home + 1))) {
			ch_PreloadCharacterMotions((*(char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_184), 0x10, s->names[0], s->names[1], s->names[2], s->names[3],
				     s->names[4], s->names[5], s->names[6], s->names[7], s->names[8], s->names[9],
				     s->names[10], s->names[11], s->names[12], s->names[13], s->names[14],
				     s->names[15]);
		}
	}
}
