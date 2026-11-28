extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* ADDRESS: GOLDTL 0x0050c4e0 */
/* ADDRESS: GOLDDE 0x004f7280 */
int __cdecl gm_GetBuildingProtLevel(unsigned char* arg)
{
	unsigned char* p;

	p = (unsigned char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned int) *arg];
	switch ((((BUILDING_PROTOTYPE*)p)->category)) {
	case 4:
		return (((BUILDING_PROTOTYPE*)p)->level);
	case 2:
	case 5:
	case 7:
		return (((BUILDING_PROTOTYPE*)p)->level);
	case 11:
	case 12:
	case 13:
	case 16:
	case 19:
		return (((BUILDING_PROTOTYPE*)p)->level);
	}
	return (((BUILDING_PROTOTYPE*)p)->level);
}
