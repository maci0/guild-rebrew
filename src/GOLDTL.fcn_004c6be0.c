// FUNCTION: GOLDTL 0x4c6be0
// SIZE: 67

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6be0(char* a1, char* a2)
{
	char buf[0x9c];

	buf[0] = 0x5e;
	*(int*) (buf + 0x14) = *(int*) (a1 + 1);
	memcpy(buf + 0x18, a2, 0x1c);
	fcn_004c4330(buf);
}
