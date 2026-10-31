


#include <string.h>

extern char g_679060[];

int __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl fcn_004f93f0(unsigned char* a1, int* a2)
{
	char buf[0x400];

	if (*a2 != 3 && *a2 != 1) {
		return 1;
	}
	if (a1[0x166] != 0x17 && a1[0x166] != 0x13) {
		return 1;
	}
	if (*a2 == 3 && a1[2] == 6) {
		memset(buf, 0, sizeof(buf));
		io_FormatTextBuffer(buf, 0x1dd5, (a1[9] != 0 ? 0x27b : 0x253) + a1[0x166]);
		fcn_004fa5f0(buf, 1, 0x657c7);
		return 2;
	}
	if (*a2 == 1 && a1[2] == 6) {
		io_FormatTextBuffer((char*) a2 + 0x14, (int) g_679060, 0x1dd4);
	}
	return 2;
}
