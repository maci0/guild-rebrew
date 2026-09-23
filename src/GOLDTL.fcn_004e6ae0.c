// FUNCTION: GOLDTL 0x4e6ae0
// SIZE: 46

#include <string.h>

#pragma intrinsic(memcpy, memset)

char* __cdecl fcn_004e6ab0(void);

void __cdecl fcn_004e6ae0(void* src)
{
	char* p;

	p = fcn_004e6ab0();
	if (p == 0) {
		return;
	}
	memcpy(p, src, 0x114);
	*(int*) p = *(int*) 0x699368;
	if (*(char*) (p + 0x31) == 0) {
		*(char*) (p + 0x31) = 8;
	}
}
