


#include <string.h>

extern char str_fmt_s[];

int __cdecl d2_ShowPrivilegMessage(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, short);

/* ADDRESS: GOLDDE 0x004e4f00 */
int __cdecl gm_HandleBuergermeisterPrivilege(unsigned char* entity, int* command)
{
	char buf[0x800];

	if (*command != 3 && *command != 1) {
		return 1;
	}
	if (entity[0x166] != 0xf) {
		return 1;
	}
	if (*command == 3 && entity[2] == 6) {
		memset(buf, 0, sizeof(buf));
		io_FormatTextBuffer(buf, 0x1dc7, *(short*) entity);
		d2_ShowPrivilegMessage(buf, 2, 0x657c7);
		return 2;
	}
	if (*command == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) command + 0x14, (int) "%s", 0x1dc6);
	}
	return 2;
}
