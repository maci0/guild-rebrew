// FUNCTION: GOLDTL 0x566cb0

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
unsigned short __cdecl fcn_0042e410(int);

void __cdecl fcn_00566cb0(char* e)
{
	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 1, fcn_0042e410(0x1e) - 0x14, 0);
}
