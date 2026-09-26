unsigned short __cdecl fcn_0042e410(int);

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLD 0x0056a3a0
// SIZE: 101
// FUNCTION: GOLDTL 0x572780
// SIZE: 101

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00572780(char* o)
{
	*(pos14_7f4c00*) (o + 0x52) = *(pos14_7f4c00*) (o + 0x44);
	*(pos14_7f4c00*) (o + 0x60) = *(pos14_7f4c00*) (o + 0x44);
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 4, fcn_0042e410(0x3c), 0);
}
