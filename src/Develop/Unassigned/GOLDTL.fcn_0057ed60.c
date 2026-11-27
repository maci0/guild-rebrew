#include "Develop/DieGildeAddOn/game/building_prototype.h"


extern unsigned char* lpGebaeudePROT;
extern char* g_7746cc;

int __cdecl d2_CheckTutCh2RathausGate(int* msg)
{
	if (msg[0] == 0x19 && msg[1] != 0) {
		if (((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) msg[1]].category)) == 0xf && msg[3] == 0x10e) {
			return 1;
		}
		return 0;
	}
	if (msg[0] == 0x1a && msg[1] != 0) {
		if (((char)(((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*(unsigned char*) msg[1]].category)) == 0xf && *((short*)g_7746cc) == 0x10e) {
			return 0;
		}
		return 1;
	}
	return msg[0] != 0x1b;
}
