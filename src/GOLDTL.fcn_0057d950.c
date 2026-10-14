unsigned short __cdecl gm_RandomMod(int);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;




void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0057d950(char* o)
{
	*(pos14_7f4c00*) (o + 0x44) = g_7f4c00;
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	*(int*) (o + 0x70) = 0;
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), gm_RandomMod(2), gm_RandomMod(0x1e), 0);
}
