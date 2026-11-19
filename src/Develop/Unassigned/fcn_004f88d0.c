#include <string.h>

extern char g_679060[];

int __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

/* ADDRESS: GOLDTL 0x004f88d0 */
int __cdecl fcn_004f88d0(unsigned char* entity, int* request)
{
	char buf[0x200];

	if (*request != 3 && *request != 1) {
		return 1;
	}
	if (entity[0x169] < 0x1e || entity[0x169] > 0x21) {
		return 1;
	}
	if (*request == 3 && entity[2] == 6) {
		memset(buf, 0, sizeof(buf));
		io_FormatTextBuffer(buf, 0x1daa, (entity[9] ? 0x27b : 0x253) + entity[0x169]);
		fcn_004fa5f0(buf, 0, 0x657c7);
		return 2;
	}
	if (*request == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1da9);
	}
	return 2;
}
