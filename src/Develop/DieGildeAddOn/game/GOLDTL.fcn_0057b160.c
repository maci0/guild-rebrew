#include "Develop/DieGildeAddOn/game/building_prototype.h"


#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad[0x24c];
};
#pragma pack()

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"



extern unsigned char* lpGebaeudePROT;


unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_004f2a10(int, unsigned char*, int, int);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl he_NotifyStorageTransfer(ENTITY_RECORD*, char*, unsigned char*, int);

void __cdecl he_RemoveAction0x92Favor(char* u)
{
	unsigned char* e;
	char* h;

	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0xac));
	if (e != 0 && ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*e].category == 0x1d) {
		fcn_004f2a10(0, e, *(int*) (u + 0xb0), *(unsigned char*) (u + 0xb4));
		h = gm_LookupEntityRecordById(*(int*) (u + 0xc));
		if (h != 0) {
			he_NotifyStorageTransfer(((ENTITY_RECORD*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (e + 0x27)]), h, e, *(int*) (u + 0xb0));
		}
	}
}
