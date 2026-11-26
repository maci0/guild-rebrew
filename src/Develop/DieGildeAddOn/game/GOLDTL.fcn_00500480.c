
#include "Develop/DieGildeAddOn/game/building_prototype.h"

extern int g_773d64;
extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;

char* __cdecl sim_StartEntityQueryByType(char* e);

char* __cdecl gm_FindFallbackPublicBuilding(char* entity, int* id, int* sub)
{
	char* found_ent;
	int idx;
	int rem;
	char* proto;

	rem = 255;
	if (*(char**) (entity + 0x170) != 0) {
		found_ent = sim_StartEntityQueryByType(*(char**) (entity + 0x170));
		if (found_ent != 0) {
			*sub = *(int*) (found_ent + 2);
		} else {
			*sub = -1;
		}
		*id = *(int*) (*(char**) (entity + 0x170) + 1);
		return *(char**) (entity + 0x170);
	}
	idx = g_773d64;
	do {
		if (((char*)lpGebaeudeINST)[idx * 169] != 0) {
			proto = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned char)((char*)lpGebaeudeINST)[idx * 169]];
			if (*proto == 3 || *proto == 0x16 || *proto == 0xf) {
				g_773d64 = idx + 1;
				*sub = -1;
				*id = *(int*) (((char*)lpGebaeudeINST) + idx * 169 + 1);
				return ((char*)lpGebaeudeINST) + idx * 169;
			}
		}
		idx = (idx + 1) % 256;
	} while (--rem != 0);
	return 0;
}
