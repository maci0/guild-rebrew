

#include <string.h>

extern char g_679060[];

int __cdecl d2_ShowPrivilegMessage(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl gm_HandleOffice0x11Privilege(unsigned char* entity, int* context)
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
		d2_ShowPrivilegMessage(buf, 1, 0x657c7);
		return 2;
	}
	if (*context == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) context + 0x14, (int) "%s", 0x1dbb);
	}
	return 2;
}
