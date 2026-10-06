#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;

unsigned short __cdecl fcn_0042e410(int);

// FUNCTION: GOLD 0x4a8c20
// FUNCTION: GOLDTL 0x4a8d40

int __cdecl fcn_004a8d40(int a, char* e)
{
	if (*(unsigned int*) (e + 4) % 4 == (*(int*)&g_7f4c00) % 4 && *(unsigned int*) (e + 4) % 8 == (unsigned short) (*(int*)&g_7f4c04) % 8)
		return fcn_0042e410(4) == 0;
	return 0;
}
