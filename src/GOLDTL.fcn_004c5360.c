// FUNCTION: GOLDTL 0x4c5360
// SIZE: 51

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5360(void)
{
	char buf[0x9c];

	buf[0] = 0x16;
	memcpy(buf + 0x10, (void*) 0x00aed220, 0x7c);
	fcn_004c4330(buf);
}
