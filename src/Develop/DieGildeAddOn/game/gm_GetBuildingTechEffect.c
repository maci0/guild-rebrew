#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;

void* __cdecl gm_QueryEntities(int list, int a, int b, int c, int d);
int __cdecl gm_GetEntityMood(unsigned char* e);

int __cdecl gm_GetBuildingTechEffect(unsigned char* e, int kind, int flag)
{
	BUILDING_PROTOTYPE* t;
	int sum;
	int i;
	int w;

	sum = 0;
	t = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[e[0]];
	for (i = 0; i < 0x40; i++) {
		w = t->components[i] & 0x7fff;
		if (w != 0 && t->component_kind[i] == kind && gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, w)) {
			sum += t->component_value[i];
		}
	}
	if (flag) {
		return (int) (sum * (gm_GetEntityMood(e) * 0.01) + 0.5);
	}
	return sum;
}
