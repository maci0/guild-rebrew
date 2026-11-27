extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"



unsigned char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl ahm_CheckFlag(unsigned char*);

void __cdecl gm_CountBuildingWorkers(char* o)
{
	int i;
	unsigned char* e;
	BUILDING_PROTOTYPE *t;

	*(int*) (o + 0x14) = 0;
	*(int*) (o + 0x18) = 0;
	for (i = 0; i < 8; i++) {
		if (((int*) (o + 0x8c))[i] != -1) {
			e = gm_LookupEntityRecordById(((int*) (o + 0x8c))[i]);
			if (e != 0 && *(unsigned char**) (e + 0x16c) != 0) {
				t = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[**(unsigned char**) (e + 0x16c)];
				if (e[0x165] == t->role_22f) {
					(*(int*) (o + 0x14))++;
				} else if (e[0x165] == t->role_230) {
					(*(int*) (o + 0x18))++;
				} else if (t->category == 0x1e && ahm_CheckFlag(e) != 0) {
					(*(int*) (o + 0x14))++;
				}
			}
		}
	}
}
