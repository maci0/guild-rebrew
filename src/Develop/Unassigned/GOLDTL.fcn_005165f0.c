extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"



#include <string.h>

void __cdecl SelectTextureSet(char*, int, int, int);

char __cdecl fcn_005165f0(char* o, unsigned char* e)
{
	BUILDING_PROTOTYPE *t;
	int n;
	int st;
	int i;

	t = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*e];
	n = t->level - 1;
	if (t->category == 2) {
		n++;
	}
	st = *(int*) (o + 0x220);
	if (st == 2 || st == 4 || st == 3) {
		return 1;
	}
	if (strncmp(o, "pfl_", 4) != 0 && strncmp(o, "vg_", 3) != 0 &&
	    strncmp(o, "!vg_", 4) != 0) {
		for (i = 0; i <= n; i++) {
			SelectTextureSet(o, *(int*) (o + 0x1cc), i, 1);
		}
	}
	return 1;
}
