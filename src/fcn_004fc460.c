// FUNCTION: GOLDTL 0x4fc460
// SIZE: 46

#include <string.h>

#pragma intrinsic(memcpy, memset)

float __cdecl fcn_004fc460(char* p)
{
	float v;

	if (p == 0) {
		return *(float*) 0x6628a8;
	}
	memcpy(p, (void*) 0x99f5e0, 40);
	v = *(float*) (p + 0x24);
	*(int*) (p + 0x18) = *(int*) 0x773d4c;
	return v;
}
