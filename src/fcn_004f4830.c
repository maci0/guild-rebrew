// FUNCTION: GOLDTL 0x4f4830
// SIZE: 43

#include <string.h>

#pragma intrinsic(memcpy, memset)

int __cdecl fcn_004f4830(int idx, void* dst)
{
	if (idx >= 0x1d) {
		return 0;
	}
	memcpy(dst, (void*) (0x68ff68 + idx * 36), 36);
	return 1;
}
