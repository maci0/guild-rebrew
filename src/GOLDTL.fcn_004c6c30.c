// FUNCTION: GOLDTL 0x4c6c30
// SIZE: 56

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6c30(char* a1)
{
	char buf[0x9c];

	buf[0] = 0x60;
	memcpy(buf + 0x10, a1, 0x1f);
	fcn_004c4330(buf);
}
