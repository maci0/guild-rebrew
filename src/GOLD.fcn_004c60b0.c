#include <string.h>

#pragma intrinsic(memcpy, memset)

void __cdecl fcn_004c4330(void* a);

/* ADDRESS: GOLD 0x004c60b0 */
void __cdecl fcn_004c60b0(char* a1)
{
	char buf[0x9c];

	buf[0] = 0x60;
	memcpy(buf + 0x10, a1, 0x1f);
	fcn_004c4330(buf);
}
