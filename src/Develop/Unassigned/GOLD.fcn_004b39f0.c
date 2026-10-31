extern char g_10069a0[];
extern char g_10069a0[];


// fcn_004b39f0 — zeroes 0x1200 bytes at the shared buffer, returns 1.
// (GOLDTL 0x10069a0 / GOLD 0xf82320.)

#include <string.h>

int __cdecl fcn_004b3b60(void)
{
	memset(g_10069a0, 0, 0x1200);
	return 1;
}
