#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_0050c4e0(unsigned char* e);

int __cdecl fcn_0050c550(unsigned char* e, unsigned char* x)
{
	BUILDING_PROTOTYPE *t;
	int n;
	int lvl;

	t = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[e[0]];
	lvl = 0;
	n = fcn_0050c4e0(x);
	if (t->level == 1) {
		lvl = 1;
	} else if (t->level == 2) {
		lvl = 2;
	} else if (t->level == 3) {
		lvl = 7;
	}
	return lvl >= n;
}
