#include <string.h>

extern char str_fmt_s[];

int __cdecl d2_ShowPrivilegMessage(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

/* ADDRESS: GOLDTL 0x004f89b0 */
/* ADDRESS: GOLDDE 0x004e4790 */
int __cdecl gm_HandleOfficeAppealPrivilege(unsigned char* entity, int* context)
{
	char buf[0x400];

	if (*context != 3 && *context != 1) {
		return 1;
	}
	if (entity[0x166] != 0x14 && entity[0x166] != 0x18 && entity[0x166] != 0x19) {
		return 1;
	}
	if (*context == 3 && entity[2] == 6) {
		memset(buf, 0, sizeof(buf));
		io_FormatTextBuffer(buf, 0x1dac, (entity[9] ? 0x27b : 0x253) + entity[0x166]);
		d2_ShowPrivilegMessage(buf, 1, 0x657c7);
		return 2;
	}
	if (*context == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) context + 0x14, (int) "%s", 0x1dab);
	}
	return 2;
}
