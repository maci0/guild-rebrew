// FUNCTION: GOLD 0x00548bc0
// FUNCTION: GOLDTL 0x550ba0

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);

void __cdecl fcn_00550ba0(char* u)
{
	*(pos14_7f4c00*) (u + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (u + 0x52), 0x18, 0, 0);
}
