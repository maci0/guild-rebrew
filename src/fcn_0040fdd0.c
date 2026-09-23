// FUNCTION: GOLD 0x40eec0
// SIZE: 48
// FUNCTION: GOLDTL 0x40fdd0
// SIZE: 48

#include <string.h>

#pragma intrinsic(strlen, strcpy, strcat)

int __cdecl fcn_0040fdd0(int* a1, int* a2)
{
	char* dst;

	dst = (char*) *a1;
	if (dst == 0) {
		return 0;
	}
	strcpy(dst, (char*) *a2);
	return 1;
}
