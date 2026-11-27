extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"



#include <string.h>

void __cdecl SelectTextureSet(char*, int, int, int);

char __cdecl d3_ApplyBuildingTextureSet(char* obj, unsigned char* ent)
{
	BUILDING_PROTOTYPE *proto;
	int max_level;
	int state;
	int i;

	proto = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*ent];
	max_level = proto->level - 1;
	if (proto->category == 2) {
		max_level++;
	}
	state = *(int*) (obj + 0x220);
	if (state == 2 || state == 4 || state == 3) {
		return 1;
	}
	if (strncmp(obj, "pfl_", 4) != 0 && strncmp(obj, "vg_", 3) != 0 &&
	    strncmp(obj, "!vg_", 4) != 0) {
		for (i = 0; i <= max_level; i++) {
			SelectTextureSet(obj, *(int*) (obj + 0x1cc), i, 1);
		}
	}
	return 1;
}
