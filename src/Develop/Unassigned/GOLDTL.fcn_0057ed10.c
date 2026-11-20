#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;
extern char* g_7746cc;

int __cdecl fcn_0057ed10(int* msg)
{
	unsigned char* e;

	if (*msg == 0x1a) {
		e = (unsigned char*) msg[1];
		if (e != 0) {
			if (((char) ((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*e].category) == 0x12 && *((short*)g_7746cc) == 0x74) {
				return 0;
			}
		}
	}
	return 1;
}
