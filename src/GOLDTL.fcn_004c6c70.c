// FUNCTION: GOLD 0x004c60f0
// SIZE: 54
// FUNCTION: GOLDTL 0x4c6c70
// SIZE: 54

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6c70(char* a1)
{
	char buf[0x9c];

	buf[0] = 0x61;
	memcpy(buf + 0x10, a1, 0x19);
	fcn_004c4330(buf);
}
