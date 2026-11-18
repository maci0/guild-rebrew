


#include <string.h>

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c62c0(void* src)
{
	char buf[0x9c];

	buf[0] = 0x41;
	memcpy(buf + 0x10, src, 0x3a);
	fcn_004c4330(buf);
}
