


#include <string.h>

extern char str_fmt_s[];

int __cdecl d2_ShowPrivilegMessage(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

/* ADDRESS: GOLDDE 0x004e51d0 */
int __cdecl gm_HandleSpionageDurationPrivilege(unsigned char* entity, int* request)
{
	char buf[0x400];

	if (*request != 3 && *request != 1) {
		return 1;
	}
	if (entity[0x166] != 0x17 && entity[0x166] != 0x13) {
		return 1;
	}
	if (*request == 3 && entity[2] == 6) {
		memset(buf, 0, sizeof(buf));
		io_FormatTextBuffer(buf, 0x1dd5, (entity[9] != 0 ? 0x27b : 0x253) + entity[0x166]);
		d2_ShowPrivilegMessage(buf, 1, 0x657c7);
		return 2;
	}
	if (*request == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1dd4);
	}
	return 2;
}
