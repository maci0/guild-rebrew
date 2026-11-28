extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* ADDRESS: GOLDTL 0x00504ef0 */
/* ADDRESS: GOLDDE 0x004f0270 */
int __cdecl gm_FindBuildingPrototypesByCategory(int type, int* out)
{
	int n;
	int i;

	n = 0;
	for (i = 0; i < 0x58; i++) {
		if (((BUILDING_PROTOTYPE*)lpGebaeudePROT)[i].category == type) {
			out[n] = i;
			n++;
		}
	}
	return n;
}
