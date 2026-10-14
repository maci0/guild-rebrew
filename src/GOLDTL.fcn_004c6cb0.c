


#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6cb0(char* a1)
{
	char buf[0x9c];

	buf[0] = 0x62;
	memcpy(buf + 0x10, a1, 0x19);
	fcn_004c4330(buf);
}
