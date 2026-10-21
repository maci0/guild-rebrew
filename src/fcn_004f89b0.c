#include <string.h>

extern char g_679060[];

int __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl fcn_0051af00(void*, int, ...);

/* ADDRESS: GOLDTL 0x004f89b0 */
int __cdecl fcn_004f89b0(unsigned char* a1, int* a2)
{
	char buf[0x400];

	if (*a2 != 3 && *a2 != 1) {
		return 1;
	}
	if (a1[0x166] != 0x14 && a1[0x166] != 0x18 && a1[0x166] != 0x19) {
		return 1;
	}
	if (*a2 == 3 && a1[2] == 6) {
		memset(buf, 0, sizeof(buf));
		fcn_0051af00(buf, 0x1dac, 0x253 + (a1[9] ? 0x28 : 0) + a1[0x169]);
		fcn_004fa5f0(buf, 1, 0x657c7);
		return 2;
	}
	if (*a2 == 1 && a1[2] == 6) {
		fcn_0051af00((char*) a2 + 0x14, (int) g_679060, 0x1dab);
	}
	return 2;
}
