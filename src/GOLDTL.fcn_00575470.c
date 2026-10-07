#include "client_types.h"
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

extern pos14_7f4c00 g_7f4c00;

// FUNCTION: GOLDTL 0x575470

void __cdecl fcn_00575470(char* o)
{
	*(pos14_7f4c00*) (o + 0x52) = *(pos14_7f4c00*) (o + 0x44);
	*(int*) (o + 0x70) = 0;
	*(pos14_7f4c00*) (o + 0x60) = *(pos14_7f4c00*) (o + 0x44);
	*(int*) (o + 0xac) = -1;
	fcn_00500bb0((pos14_7f4c00*) (o + 0x52), 0, 0xa, 0);
}
