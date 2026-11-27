





// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl he_InitSimulateWirtshaus(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	*(short*) (e + 0x56) = 0x16;
	*(int*) (e + 0x58) = 0x1e;
	*(int*) (e + 0x5c) = 0;
	*(int*) (e + 0xac) = 0;
	*(int*) (e + 0xb0) = 0;
}
