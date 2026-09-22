// FUNCTION: GOLDTL 0x4ce3e0
// SIZE: 65

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004ce3e0(int a1)
{
	char buf[0x9c];

	memset(buf + 0x10, 0, 0x80);
	buf[0] = 0x5f;
	*(int*) (buf + 0x10) = 5;
	*(int*) (buf + 0x14) = a1;
	fcn_004c4330(buf);
}
