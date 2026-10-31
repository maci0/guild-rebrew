


#include <string.h>

extern char g_679060[];

int __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, short);

int __cdecl fcn_004f9120(unsigned char* a1, int* a2)
{
	char buf[0x800];

	if (*a2 != 3 && *a2 != 1) {
		return 1;
	}
	if (a1[0x166] != 0xf) {
		return 1;
	}
	if (*a2 == 3 && a1[2] == 6) {
		memset(buf, 0, sizeof(buf));
		io_FormatTextBuffer(buf, 0x1dc7, *(short*) a1);
		fcn_004fa5f0(buf, 2, 0x657c7);
		return 2;
	}
	if (*a2 == 1 && a1[2] == 6) {
		io_FormatTextBuffer((char*) a2 + 0x14, (int) g_679060, 0x1dc6);
	}
	return 2;
}
