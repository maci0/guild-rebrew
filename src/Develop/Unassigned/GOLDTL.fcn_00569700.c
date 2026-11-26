





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl he_InitAction0x3d(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	*(pos14_7f4c00*) (e + 0xb4) = (*(pos14_7f4c00*)&gm_GameTime);
}
