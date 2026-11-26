unsigned short __cdecl gm_RandomMod(int);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;




void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00572780(char* o)
{
	*(pos14_7f4c00*) (o + 0x52) = *(pos14_7f4c00*) (o + 0x44);
	*(pos14_7f4c00*) (o + 0x60) = *(pos14_7f4c00*) (o + 0x44);
	gm_AddTime((pos14_7f4c00*) (o + 0x52), 4, gm_RandomMod(0x3c), 0);
}
