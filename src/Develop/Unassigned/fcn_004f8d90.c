#include <string.h>

#pragma intrinsic(memset)

void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_004fa5f0(void*, int, char*);

/* ADDRESS: GOLDTL 0x004f8d90 */
int __cdecl fcn_004f8d90(char* a0, int* a1)
{
	char buf[0x400];
	char sep;

	if (*a1 != 3 && *a1 != 1) {
		return 1;
	}
	if (*(unsigned char*) (a0 + 0x166) != 0x11) {
		return 1;
	}
	sep = 6;
	if (*a1 == 3) {
		if (*(unsigned char*) (a0 + 2) == sep) {
			memset(buf, 0, 0x400);
			io_FormatTextBuffer(buf, 0x1dbe,
				*(unsigned char*) (a0 + 9) ? 0x28c : 0x264);
			fcn_004fa5f0(buf, 1, (char*) 0x657c7);
			return 2;
		}
	}
	if (*a1 == 1) {
		if (*(unsigned char*) (a0 + 2) == sep) {
			io_FormatTextBuffer((char*) a1 + 0x14, 0x679060, 0x1dbd);
		}
	}
	return 2;
}
