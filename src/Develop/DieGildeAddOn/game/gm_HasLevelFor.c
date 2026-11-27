#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;

int __cdecl gm_GetBuildingProtLevel(unsigned char* e);

int __cdecl gm_HasLevelFor(unsigned char* e, unsigned char* x)
{
	BUILDING_PROTOTYPE *t;
	int n;
	int lvl;

	t = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[e[0]];
	lvl = 0;
	n = gm_GetBuildingProtLevel(x);
	if (t->level == 1) {
		lvl = 1;
	} else if (t->level == 2) {
		lvl = 2;
	} else if (t->level == 3) {
		lvl = 7;
	}
	return lvl >= n;
}
