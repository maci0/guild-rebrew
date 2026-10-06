// FUNCTION: GOLD 0x5510f0
// FUNCTION: GOLDTL 0x5591c0

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_005591c0(char* e)
{
	*(int*) (e + 0x70) = 0;
	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	*(short*) (e + 0x56) = 7;
	*(int*) (e + 0x58) = 0;
}
