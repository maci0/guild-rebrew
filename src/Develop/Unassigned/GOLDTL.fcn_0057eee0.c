#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;

int __cdecl d2_AllowTutCh2Cat0fOr02Or12Msg19(int* msg)
{
	unsigned char* e;
	char* t;

	if (*msg == 0x19) {
		e = (unsigned char*) msg[1];
		if (e != 0) {
			t = (char*)&((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e];
			if (((char)(((BUILDING_PROTOTYPE*)t)->category)) != 0xf && ((char)(((BUILDING_PROTOTYPE*)t)->category)) != 2 && ((char)(((BUILDING_PROTOTYPE*)t)->category)) != 0x12) {
				return 0;
			}
		}
	}
	return 1;
}
