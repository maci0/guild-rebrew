





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_005492e0(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	if (e[0x78] & 2) {
		fcn_004c5620(-1, e);
	}
}
