





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl fcn_00569700(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	*(pos14_7f4c00*) (e + 0xb4) = (*(pos14_7f4c00*)&gm_GameTime);
}
