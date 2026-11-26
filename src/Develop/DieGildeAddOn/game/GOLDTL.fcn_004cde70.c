


char* __cdecl gm_FindRecordById(int);
#include "Develop/DieGildeAddOn/game/spiel.h"

int __cdecl cm_ExClearObjektResources(char* packet, char* reply)
{
	char* node;

	if (reply != 0) {
		reply[0] = 2;
		reply[1] = 0;
		*(int*) (reply + 6) = 0;
	}
	node = gm_FindRecordById(*(int*) (packet + 0x10));
	if (node == 0) {
		return -1;
	}
	if (*(int*) (node + 0x29) != 0) {
		rt_FreeRoutePoints(*(char**) (node + 0x29));
		*(int*) (node + 0x29) = 0;
	}
	if (reply != 0) {
		*reply = 1;
	}
	return 0;
}
