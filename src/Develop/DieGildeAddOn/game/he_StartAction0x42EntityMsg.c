





// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

int __cdecl gm_RandomMod(int);

void __cdecl he_StartAction0x42EntityMsg(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = (*(pos14_7f4c00*)&gm_GameTime);
	*(short*) (e + 0x56) = gm_RandomMod(10) + 10;
	*(int*) (e + 0x58) = (unsigned short) gm_RandomMod(0x3b);
	*(int*) (e + 0x5c) = 0;
}
