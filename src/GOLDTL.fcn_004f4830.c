// GLOBAL: GOLDTL 0x68ff68
extern char g_68ff68[];
// GLOBAL: GOLD 0x611238
extern char g_68ff68[];
// FUNCTION: GOLD 0x004f2720
// FUNCTION: GOLDTL 0x4f4830

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

extern unsigned short g_774970;
extern char g_7f4ca0[];

char* __cdecl fcn_00508e40(int id);
void __cdecl fcn_004f5110(char* buf, int k);
void __cdecl fcn_005b26e0(char* o, char* buf);

// FUNCTION: GOLD 0x4f27d0
// FUNCTION: GOLDTL 0x004f48e0
int __cdecl fcn_004f48e0(char* s)
{
	int rec[9];
	char buf[0x100];
	char* o;

	if (fcn_004f4830(*(unsigned char*) (s + 4), rec) == 0) {
		return 0;
	}
	*(int*) (g_68ff68 + *(unsigned char*) (s + 4) * 36 + 0x18) = *(int*) (s + 5);
	if (*(int*) (g_7f4ca0 + g_774970 * 0x21c + 4) != *(int*) s) {
		o = fcn_00508e40(*(int*) s);
		if (o != 0) {
			fcn_004f5110(buf, *(unsigned char*) (s + 4));
			fcn_005b26e0(o, buf);
		}
	}
	return 1;
}

extern char g_9a3825[];

// FUNCTION: GOLD 0x4f39e0
// FUNCTION: GOLDTL 0x004f5dd0

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
