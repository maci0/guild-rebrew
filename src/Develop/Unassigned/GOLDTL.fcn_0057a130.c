





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl fcn_00500bb0(char*, int, int, int);

void __cdecl fcn_0057a130(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	*(int*) (e + 0x70) = 0;
	fcn_00500bb0(e + 0x52, 0x48, 0, 0);
}
