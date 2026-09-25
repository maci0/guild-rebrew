// FUNCTION: GOLD 0x004f6c60
// SIZE: 196
// FUNCTION: GOLDTL 0x004f9050
// SIZE: 196

#include <string.h>

extern char g_679060[];

int __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl fcn_0051af00(void*, int, short);

int __cdecl fcn_004f9050(unsigned char* a1, int* a2)
{
	char buf[0x800];

	if (*a2 != 3 && *a2 != 1) {
		return 1;
	}
	if (a1[0x166] != 0xa) {
		return 1;
	}
	if (*a2 == 3 && a1[2] == 6) {
		memset(buf, 0, sizeof(buf));
		fcn_0051af00(buf, 0x1dc5, *(short*) a1);
		fcn_004fa5f0(buf, 2, 0x657c7);
		return 2;
	}
	if (*a2 == 1 && a1[2] == 6) {
		fcn_0051af00((char*) a2 + 0x14, (int) g_679060, 0x1dc4);
	}
	return 2;
}
