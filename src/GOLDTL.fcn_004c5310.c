

#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5310(int a1, unsigned short a2, char* a3)
{
	char buf[0x9c];

	buf[0] = 0x15;
	*(int*) (buf + 0x10) = a1;
	*(unsigned short*) (buf + 0x14) = a2;
	memcpy(buf + 0x16, a3, 0x1f);
	fcn_004c4330(buf);
}
