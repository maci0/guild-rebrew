





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl sim_SetSyncParams(char*, int, int, int);

void __cdecl fcn_0057b330(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	sim_SetSyncParams(e + 0x52, 6, 0, 0);
	*(pos14_7f4c00*) (e + 0x60) = *(pos14_7f4c00*) (e + 0x52);
}
