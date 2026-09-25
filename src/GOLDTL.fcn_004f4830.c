// GLOBAL: GOLDTL 0x68ff68
extern char g_68ff68[];
// GLOBAL: GOLD 0x611238
extern char g_68ff68[];
// FUNCTION: GOLD 0x004f2720
// SIZE: 48
// FUNCTION: GOLDTL 0x4f4830
// SIZE: 43

#include <string.h>

#pragma intrinsic(memcpy, memset)

int __cdecl fcn_004f4830(int idx, void* dst)
{
	if (idx >= 0x1d) {
		return 0;
	}
	memcpy(dst, (void*) (g_68ff68 + idx * 36), 36);
	return 1;
}

extern char g_9a3825[];

// FUNCTION: GOLDTL 0x004f5dd0
// SIZE: 70

int __cdecl fcn_004f5dd0(int a)
{
	int buf[9];
	int s;
	int p;

	s = 0;
	for (p = (int) g_9a3825; p < (int) (g_9a3825 + 0x5a00); p += 0x2d) {
		if (*(int*) (p - 0xf) == a && *(int*) p == 1) {
			fcn_004f4830(*(unsigned char*) (p - 9), buf);
			s += buf[3];
		}
	}
	return s;
}
