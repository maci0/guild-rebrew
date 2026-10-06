// FUNCTION: GOLD 0x005880b0
// fcn_005880b0 — zeroes the 0x4000-byte table at 0x6f5f60.

#include <string.h>

void __cdecl fcn_005880b0(void)
{
	memset((void*) 0x6f5f60, 0, 0x4000);
}
