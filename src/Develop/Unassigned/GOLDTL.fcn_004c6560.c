


#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6560(char* src)
{
	char buf[0x9c];
	char* p;

	p = buf;
	*(char*) p = 0x4b;
	memcpy(p + 0x10, src, 0x80);
	fcn_004c4330(p);
}
