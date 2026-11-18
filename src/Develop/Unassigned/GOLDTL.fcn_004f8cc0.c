

#include <string.h>

extern char g_679060[];

int __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl fcn_004f8cc0(unsigned char* entity, int* context)
{
	char buf[0x400];

	if (*context != 3 && *context != 1) {
		return 1;
	}
	if (entity[0x166] != 0x11) {
		return 1;
	}
	if (*context == 3 && entity[2] == 6) {
		memset(buf, 0, sizeof(buf));
		io_FormatTextBuffer(buf, 0x1dbc, entity[9] != 0 ? 0x28c : 0x264);
		fcn_004fa5f0(buf, 1, 0x657c7);
		return 2;
	}
	if (*context == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) context + 0x14, (int) g_679060, 0x1dbb);
	}
	return 2;
}
