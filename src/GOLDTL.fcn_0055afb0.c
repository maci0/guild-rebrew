void __cdecl fcn_0055afb0(char*);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x00552e80
// SIZE: 100
// FUNCTION: GOLDTL 0x55afb0
// SIZE: 100

void __cdecl fcn_0055afb0(char* o)
{
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	*(pos14_7f4c00*) (o + 0xac) = g_7f4c00;
	*(int*) (o + 0x70) = 0;
}
