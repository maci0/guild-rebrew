#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;

int __cdecl fcn_0057eea0(int* msg)
{
	unsigned char* e;
	char* t;

	if (*msg == 0x19) {
		e = (unsigned char*) msg[1];
		if (e != 0) {
			t = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e];
			if ((char)((BUILDING_PROTOTYPE*)t)->category != 0xf && (char)((BUILDING_PROTOTYPE*)t)->category != 2) {
				return 0;
			}
		}
	}
	return 1;
}
