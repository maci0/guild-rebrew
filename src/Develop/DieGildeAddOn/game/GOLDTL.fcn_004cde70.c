


char* __cdecl gm_FindRecordById(int);
#include "Develop/DieGildeAddOn/game/spiel.h"

int __cdecl fcn_004cde70(char* packet, char* reply)
{
	char* p;

	if (reply != 0) {
		reply[0] = 2;
		reply[1] = 0;
		*(int*) (reply + 6) = 0;
	}
	p = gm_FindRecordById(*(int*) (packet + 0x10));
	if (p == 0) {
		return -1;
	}
	if (*(int*) (p + 0x29) != 0) {
		fcn_004be280(*(char**) (p + 0x29));
		*(int*) (p + 0x29) = 0;
	}
	if (reply != 0) {
		*reply = 1;
	}
	return 0;
}
