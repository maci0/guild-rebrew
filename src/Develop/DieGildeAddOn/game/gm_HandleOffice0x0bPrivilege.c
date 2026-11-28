


#include <string.h>

extern char str_fmt_s[];

void __cdecl io_FormatTextBuffer(void* p, ...);
void __cdecl d2_ShowPrivilegMessage(char* text, int a, int b);

int __cdecl gm_HandleOffice0x0bPrivilege(char* entity, int* command)
{
	char buf[512];

	if (*command != 3 && *command != 1) {
		return 1;
	}
	if (entity[0x166] != 0xb) {
		return 1;
	}
	if (*command == 3 && entity[2] == 6) {
		memset(buf, 0, sizeof(buf));
		io_FormatTextBuffer(buf, 0x1da0, entity[9] != 0 ? 0x286 : 0x25e);
		d2_ShowPrivilegMessage(buf, 0, 0x657c7);
		return 2;
	}
	if (*command == 1 && entity[2] == 6) {
		io_FormatTextBuffer(command + 5, "%s", 0x1d9f);
	}
	return 2;
}
