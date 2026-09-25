// GLOBAL: GOLDTL 0x9badd0
extern int g_9badd0;
// FUNCTION: GOLD 0x004cd6a0
// SIZE: 63
// FUNCTION: GOLDTL 0x4ce260
// SIZE: 63

#include <string.h>

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004ce260(int a1)
{
	char buf[0x9c];

	memset(buf + 0x10, 0, 0x80);
	buf[0] = 0x5f;
	*(int*) (buf + 0x10) = 3;
	*(int*) (buf + 0x14) = g_9badd0;
	fcn_004c4330(buf);
}
