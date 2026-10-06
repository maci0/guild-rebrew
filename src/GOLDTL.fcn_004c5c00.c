// GLOBAL: GOLDTL 0x68ae64
extern char g_68ae64[];
// FUNCTION: GOLD 0x004c51b0
// FUNCTION: GOLDTL 0x4c5c00

#include <string.h>

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_0041d9e0(char*);

void __cdecl fcn_004c5c00(int a1, int a2, int a3, char* a4)
{
	char buf[0x9c];

	buf[0] = 0x30;
	*(int*) (buf + 0x10) = a1;
	*(int*) (buf + 0x14) = a2;
	*(int*) (buf + 0x18) = a3;
	if (strlen(a4) < 0x20) {
		strcpy(buf + 0x1c, a4);
	} else {
		fcn_0041d9e0(g_68ae64);
	}
	fcn_004c4330(buf);
}
