// FUNCTION: GOLD 0x004f60b0
// SIZE: 208
// FUNCTION: GOLDTL 0x004f84a0
// SIZE: 208

#include <string.h>

extern char g_679060[];

void __cdecl fcn_0051af00(void* p, ...);
void __cdecl fcn_004fa5f0(char* text, int a, int b);

int __cdecl fcn_004f84a0(char* a, int* b)
{
	char buf[512];

	if (*b != 3 && *b != 1) {
		return 1;
	}
	if (a[0x166] != 0xb) {
		return 1;
	}
	if (*b == 3 && a[2] == 6) {
		memset(buf, 0, sizeof(buf));
		fcn_0051af00(buf, 0x1da0, a[9] != 0 ? 0x286 : 0x25e);
		fcn_004fa5f0(buf, 0, 0x657c7);
		return 2;
	}
	if (*b == 1 && a[2] == 6) {
		fcn_0051af00(b + 5, g_679060, 0x1d9f);
	}
	return 2;
}
