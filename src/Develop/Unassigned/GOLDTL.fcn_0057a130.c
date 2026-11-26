





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl gm_AddTime(char*, int, int, int);

void __cdecl fcn_0057a130(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	*(int*) (e + 0x70) = 0;
	gm_AddTime(e + 0x52, 0x48, 0, 0);
}
