// GLOBAL: GOLDTL 0x102cbc0
extern char g_102cbc0[];
// GLOBAL: GOLD 0xfa5aa0
extern char g_102cbc0[];
// FUNCTION: GOLD 0x0046c5f0
// SIZE: 37
// FUNCTION: GOLDTL 0x469510
// SIZE: 37

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_00469510(int i)
{
	memset((void*) (g_102cbc0 + i * 140), 0, 0x8c);
}
