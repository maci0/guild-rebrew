// FUNCTION: GOLD 0x004c56d0
// SIZE: 64
// FUNCTION: GOLDTL 0x4c6190
// SIZE: 64

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6190(char* a1, char a2)
{
	char buf[0x9c];

	buf[0] = 0x3f;
	*(char*) (buf + 0x10) = a2;
	memcpy(buf + 0x11, a1, 0x80);
	fcn_004c4330(buf);
}
