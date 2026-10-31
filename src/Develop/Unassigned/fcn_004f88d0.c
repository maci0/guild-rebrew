#include <string.h>

extern char g_679060[];

int __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

/* ADDRESS: GOLDTL 0x004f88d0 */
int __cdecl fcn_004f88d0(unsigned char* a1, int* a2)
{
	char buf[0x200];

	if (*a2 != 3 && *a2 != 1) {
		return 1;
	}
	if (a1[0x169] < 0x1e || a1[0x169] > 0x21) {
		return 1;
	}
	if (*a2 == 3 && a1[2] == 6) {
		memset(buf, 0, sizeof(buf));
		io_FormatTextBuffer(buf, 0x1daa, 0x253 + (a1[9] ? 0x28 : 0) + a1[0x169]);
		fcn_004fa5f0(buf, 0, 0x657c7);
		return 2;
	}
	if (*a2 == 1 && a1[2] == 6) {
		io_FormatTextBuffer((char*) a2 + 0x14, (int) g_679060, 0x1da9);
	}
	return 2;
}
