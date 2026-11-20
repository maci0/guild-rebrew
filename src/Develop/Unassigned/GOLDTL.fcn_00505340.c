extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/building_prototype.h"
/* ADDRESS: GOLDTL 0x00505340 */
int __cdecl fcn_00505340(unsigned char* e)
{
	return ((char) ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*e].category) == 10;
}
