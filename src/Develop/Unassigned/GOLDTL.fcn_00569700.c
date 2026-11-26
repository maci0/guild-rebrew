





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl he_InitAction0x3d(char* action)
{
	*(pos14_7f4c00*) (action + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	*(pos14_7f4c00*) (action + 0xb4) = (*(pos14_7f4c00*)&gm_GameTime);
}
