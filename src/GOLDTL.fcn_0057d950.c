unsigned short __cdecl fcn_0042e410(int);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x00575410
// SIZE: 139
// FUNCTION: GOLDTL 0x57d950
// SIZE: 139

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0057d950(char* o)
{
	*(pos14_7f4c00*) (o + 0x44) = g_7f4c00;
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	*(int*) (o + 0x70) = 0;
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), fcn_0042e410(2), fcn_0042e410(0x1e), 0);
}
