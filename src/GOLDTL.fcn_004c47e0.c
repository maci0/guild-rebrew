// GLOBAL: GOLDTL 0xaed2a0
extern char g_aed2a0[];
// GLOBAL: GOLD 0xa68ca0
extern char g_aed2a0[];
// FUNCTION: GOLD 0x004c3e70
// FUNCTION: GOLDTL 0x4c47e0

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c47e0(int* p)
{
	int v;

	v = p[1];
	*(char*) (g_aed2a0 + 4) = 0;
	*(int*) g_aed2a0 = v;
	memset(g_aed2a0 + 5, 0, 119);
	*(int*) (g_aed2a0 + 0x80) = 0;
	*(int*) (g_aed2a0 + 0x94) = (int) p;
}
