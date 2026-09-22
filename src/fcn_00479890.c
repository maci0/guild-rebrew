// FUNCTION: GOLDTL 0x479890
// SIZE: 36

#include <string.h>

#pragma intrinsic(memcpy, memset)

int __cdecl fcn_00479890(char* p, char* src)
{
	if (p == 0) {
		return 0;
	}
	memcpy(p + 0x445, src, 0x400);
	return 1;
}
