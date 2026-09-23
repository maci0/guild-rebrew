extern int* g_772f40;
// FUNCTION: GOLDTL 0x4c6820
// SIZE: 89

#include <string.h>

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c6820(int a1, void* a2)
{
	char buf[0x9c];

	buf[0] = 0x51;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x40) = g_772f40 != 0 ? *g_772f40 : -1;
	memcpy(buf + 0x14, a2, 0x2c);
	fcn_004c4330(buf);
}
