// FUNCTION: GOLDTL 0x4b3b60
// SIZE: 22
// FUNCTION: GOLD 0x004b39f0
// SIZE: 22
// fcn_004b39f0 — zeroes 0x1200 bytes at 0xf82320, returns 1.

#include <string.h>

int __cdecl fcn_004b39f0(void)
{
	memset((void*) 0xf82320, 0, 0x1200);
	return 1;
}
