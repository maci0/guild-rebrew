#include <string.h>

#pragma intrinsic(memcpy, memset)

int __cdecl fcn_004c4330(void*);

/* ADDRESS: GOLD 0x004cd650 */
void __cdecl fcn_004cd650(int a1)
{
	char buf[0x9c];

	memset(buf + 0x10, 0, 0x80);
	*(int*) (buf + 0x14) = *(int*) 0x9367d0;
	buf[0] = 0x5f;
	*(int*) (buf + 0x10) = 1;
	*(int*) (buf + 0x18) = a1;
	fcn_004c4330(buf);
}
