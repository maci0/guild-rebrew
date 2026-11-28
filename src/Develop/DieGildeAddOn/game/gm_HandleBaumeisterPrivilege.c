


#include <string.h>

extern char str_fmt_s[];

int __cdecl d2_ShowPrivilegMessage(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, short);

/* ADDRESS: GOLDDE 0x004e4e30 */
int __cdecl gm_HandleBaumeisterPrivilege(unsigned char* entity, int* request)
{
	char buf[0x800];

	if (*request != 3 && *request != 1) {
		return 1;
	}
	if (entity[0x166] != 0xa) {
		return 1;
	}
	if (*request == 3 && entity[2] == 6) {
		memset(buf, 0, sizeof(buf));
		io_FormatTextBuffer(buf, 0x1dc5, *(short*) entity);
		d2_ShowPrivilegMessage(buf, 2, 0x657c7);
		return 2;
	}
	if (*request == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1dc4);
	}
	return 2;
}
