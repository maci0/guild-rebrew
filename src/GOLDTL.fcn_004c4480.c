#include "client_types.h"
extern cell10_fb5760 g_fb5760[0x8000];

// FUNCTION: GOLD 0x4c3b10
// SIZE: 32
// FUNCTION: GOLDTL 0x4c4480
// SIZE: 29

int __cdecl fcn_004c4480(int i)
{
	if (i >= 0 && i < 0x8000)
		return *(int*) &((unsigned char(*)[10])g_fb5760)[i][6];
	return 0;
}
