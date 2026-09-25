// FUNCTION: GOLD 0x004c5aa0
// SIZE: 53
// FUNCTION: GOLDTL 0x4c6560
// SIZE: 53

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6560(char* a1)
{
	char buf[0x9c];
	char* p;

	p = buf;
	*(char*) p = 0x4b;
	memcpy(p + 0x10, a1, 0x80);
	fcn_004c4330(p);
}
