unsigned short __cdecl gm_RandomMod(int);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x00552450
// FUNCTION: GOLDTL 0x55a540

void __cdecl fcn_0055a540(char* o)
{
	*(int*) (o + 0x70) = 0;
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	*(short*) (o + 0x56) = gm_RandomMod(3) + 9;
	*(int*) (o + 0x58) = gm_RandomMod(4) * 15;
	*(int*) (o + 0xb0) = 0;
}
