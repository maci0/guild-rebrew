// FUNCTION: GOLD 0x004c49e0
// FUNCTION: GOLDTL 0x4c53a0

#include <string.h>

#pragma intrinsic(memcpy, memset)

extern char g_aed220[];
void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c53a0(void)
{
	char buf[0x9c];

	buf[0] = 0x17;
	memcpy(buf + 0x10, g_aed220, 0x7c);
	fcn_004c4330(buf);
}
