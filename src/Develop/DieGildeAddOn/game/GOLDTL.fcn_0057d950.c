unsigned short __cdecl gm_RandomMod(int);

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;




void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0057d950(char* o)
{
	*(pos14_7f4c00*) (o + 0x44) = gm_GameTime;
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	*(int*) (o + 0x70) = 0;
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), gm_RandomMod(2), gm_RandomMod(0x1e), 0);
}
