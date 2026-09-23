// GLOBAL: GOLDTL 0x68ff68
extern char g_68ff68[];
// GLOBAL: GOLD 0x611238
extern char g_68ff68[];
// FUNCTION: GOLD 0x004f2720
// SIZE: 48
// FUNCTION: GOLDTL 0x4f4830
// SIZE: 43

#include <string.h>

#pragma intrinsic(memcpy, memset)

int __cdecl fcn_004f4830(int idx, void* dst)
{
	if (idx >= 0x1d) {
		return 0;
	}
	memcpy(dst, (void*) (g_68ff68 + idx * 36), 36);
	return 1;
}
