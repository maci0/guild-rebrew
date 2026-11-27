unsigned short __cdecl gm_RandomMod(int);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;




void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl he_InitEvent09e(char* o)
{
	*(int*) (o + 0x70) = 0;
	*(pos14_7f4c00*) (o + 0x44) = gm_GameTime;
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (o + 0x52), 0x18, 0, 0);
	*(short*) (o + 0x56) = 6;
	*(int*) (o + 0x58) = gm_RandomMod(0x10) + 5;
}
