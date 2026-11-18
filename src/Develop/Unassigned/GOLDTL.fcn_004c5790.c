


#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c5790(char a1, char* data)
{
	char buf[0x9c];

	buf[0] = 0x20;
	*(char*) (buf + 0x10) = a1;
	if (data != 0) {
		memcpy(buf + 0x11, data, 0x7c);
	}
	fcn_004c4330(buf);
}
