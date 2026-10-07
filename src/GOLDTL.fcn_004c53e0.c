// FUNCTION: GOLD 0x004c4a20
// FUNCTION: GOLDTL 0x4c53e0

#include <string.h>

#pragma intrinsic(memcpy, memset)

extern char g_aed2a0[];
void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c53e0(void)
{
	char buf[0x9c];

	buf[0] = 0x18;
	memcpy(buf + 0x10, g_aed2a0, 0x7c);
	fcn_004c4330(buf);
}
