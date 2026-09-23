// GLOBAL: GOLDTL 0x773d38
extern int g_773d38;
// FUNCTION: GOLD 0x004c4e40
// SIZE: 80
// FUNCTION: GOLDTL 0x4c5820
// SIZE: 80

#include <string.h>

void __cdecl fcn_004c4330(void*);

int __cdecl fcn_0064d3f8(void);

void __cdecl fcn_004c5820(void* a1)
{
	char buf[0x9c];

	buf[0] = 0x22;
	memcpy(buf + 0x10, a1, 0x2d);
	*(int*) (buf + 0x10) = g_773d38;
	*(int*) (buf + 0x35) = 1;
	*(int*) (buf + 0x39) = fcn_0064d3f8();
	fcn_004c4330(buf);
}
