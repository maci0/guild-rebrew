unsigned short __cdecl fcn_0042e410(int);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x005741e0
// SIZE: 135
// FUNCTION: GOLDTL 0x57c720
// SIZE: 135

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0057c720(char* o)
{
	*(int*) (o + 0x70) = 0;
	*(pos14_7f4c00*) (o + 0x44) = g_7f4c00;
	*(pos14_7f4c00*) (o + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0x18, 0, 0);
	*(short*) (o + 0x56) = 6;
	*(int*) (o + 0x58) = fcn_0042e410(0x10) + 5;
}
