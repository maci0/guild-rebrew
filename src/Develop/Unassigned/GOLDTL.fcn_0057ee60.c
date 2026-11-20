#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_0057ee60(int* msg)
{
	unsigned char* e;

	if (*msg == 0x19) {
		e = (unsigned char*) msg[1];
		if (e != 0 && ((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e].category)) != 0xf) {
			return 0;
		}
	}
	return 1;
}
