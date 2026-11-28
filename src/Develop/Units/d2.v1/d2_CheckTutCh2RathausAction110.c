#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;

/* ADDRESS: GOLDDE 0x00564bc0 */
int __cdecl d2_CheckTutCh2RathausAction110(int* msg)
{
	unsigned char* e;

	if (*msg == 0x19) {
		e = (unsigned char*) msg[1];
		if (e != 0 && ((char) ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*e].category) == 0xf && msg[3] == 0x110) {
			return 1;
		}
	}
	return 0;
}
