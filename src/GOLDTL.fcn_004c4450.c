#include "client_types.h"
extern cell10_fb5760 g_fb5760[0x8000];

// FUNCTION: GOLD 0x4c3ae0
// FUNCTION: GOLDTL 0x4c4450

int __cdecl fcn_004c4450(int i)
{
	if (i >= 0 && i < 0x8000)
		return ((unsigned char(*)[10])g_fb5760)[i][0];
	return -1;
}
