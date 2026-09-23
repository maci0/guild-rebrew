extern int g_9badd0;
// FUNCTION: GOLDTL 0x4ce320
// SIZE: 84

#include <string.h>

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004ce320(void* a1)
{
	char buf[0x9c];

	memset(buf + 0x10, 0, 0x80);
	buf[0] = 0x5f;
	*(int*) a1 = g_9badd0;
	*(int*) (buf + 0x10) = 2;
	memcpy(buf + 0x14, a1, 0x57);
	fcn_004c4330(buf);
}
