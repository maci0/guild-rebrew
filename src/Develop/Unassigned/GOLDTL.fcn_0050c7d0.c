extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* ADDRESS: GOLDTL 0x0050c7d0 */
int __cdecl fcn_0050c7d0(int idx, int type)
{
	BUILDING_PROTOTYPE* e;
	int sum;
	int i;

	sum = 0;
	e = &((BUILDING_PROTOTYPE*)lpGebaeudePROT)[idx];
	for (i = 0; i < 0x40; i++) {
		if ((e->components[i] & 0x7fff) != 0 && e->component_kind[i] == type) {
			sum += e->component_value[i];
		}
	}
	return sum;
}
