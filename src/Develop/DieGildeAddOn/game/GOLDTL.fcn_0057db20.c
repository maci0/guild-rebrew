unsigned short __cdecl gm_RandomMod(int);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;




void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0057db20(char* o)
{
	*(pos14_7f4c00*) (o + 0x44) = gm_GameTime;
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	*(int*) (o + 0x70) = 0;
	gm_AddTime((pos14_7f4c00*) (o + 0x52), gm_RandomMod(0x20), 0, 0);
}
