

// fcn_004b39f0 — zeroes 0x1200 bytes at 0x10069a0, returns 1.

#include <string.h>

int __cdecl fcn_004b39f0(void)
{
	memset((void*) 0x10069a0, 0, 0x1200);
	return 1;
}
