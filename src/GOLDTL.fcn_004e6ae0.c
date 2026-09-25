// GLOBAL: GOLDTL 0x699368
extern int g_699368;
// GLOBAL: GOLD 0x61a638
extern int g_699368;
// FUNCTION: GOLD 0x004e5150
// SIZE: 46
// FUNCTION: GOLDTL 0x4e6ae0
// SIZE: 46

#include <string.h>

#pragma intrinsic(memcpy, memset)

char* __cdecl fcn_004e6ab0(void);

void __cdecl fcn_004e6ae0(void* src)
{
	char* p;

	p = fcn_004e6ab0();
	if (p == 0) {
		return;
	}
	memcpy(p, src, 0x114);
	*(int*) p = g_699368;
	if (*(char*) (p + 0x31) == 0) {
		*(char*) (p + 0x31) = 8;
	}
}
