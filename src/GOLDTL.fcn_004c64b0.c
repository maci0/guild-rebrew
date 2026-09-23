// FUNCTION: GOLD 0x004c59f0
// SIZE: 117
// FUNCTION: GOLDTL 0x4c64b0
// SIZE: 117

#include <string.h>

void __cdecl fcn_004c4330(void*);

void __cdecl fcn_004c64b0(char a1, int a2, int a3, char a4, char a5, char a6, char* a7)
{
	char buf[0x9c];

	buf[0] = 0x49;
	*(char*) (buf + 0x14) = a1;
	*(int*) (buf + 0x17) = a2;
	*(int*) (buf + 0x1b) = a3;
	*(char*) (buf + 0x1f) = a4;
	*(char*) (buf + 0x20) = a5;
	*(char*) (buf + 0x21) = a6;
	strcpy(buf + 0x26, a7);
	fcn_004c4330(buf);
}
