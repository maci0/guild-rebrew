





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_004c5620(int, char*);

void __cdecl fcn_0055ab40(char* e)
{
	if ((e[0x78] & 4) == 0) {
		*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
		fcn_00500bb0(e + 0x52, *(int*) (e + 0xb8), 0, 0);
		*(int*) (e + 0x84) = fcn_004c5620(0, e);
	}
}
