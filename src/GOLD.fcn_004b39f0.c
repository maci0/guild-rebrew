// GLOBAL: GOLDTL 0x10069a0
extern char g_10069a0[];
// GLOBAL: GOLD 0xf82320
extern char g_10069a0[];
// FUNCTION: GOLDTL 0x4b3b60
// FUNCTION: GOLD 0x004b39f0
// fcn_004b39f0 — zeroes 0x1200 bytes at the shared buffer, returns 1.
// (GOLDTL 0x10069a0 / GOLD 0xf82320.)

#include <string.h>

int __cdecl fcn_004b39f0(void)
{
	memset(g_10069a0, 0, 0x1200);
	return 1;
}
