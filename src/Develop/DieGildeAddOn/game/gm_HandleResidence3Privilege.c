


extern char str_fmt_s[];

int __cdecl d2_ShowPrivilegMessage(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl gm_HandleResidence3Privilege(unsigned char* entity, int* command)
{
	char buf[0x100];

	if (*command != 3 && *command != 1) {
		return 1;
	}
	if (entity[0xd] > 4) {
		return 4;
	}
	if (entity[0xd] < 4) {
		return 1;
	}
	if (*command == 3 && entity[2] == 6) {
		io_FormatTextBuffer(buf, 0x1d85, (entity[9] != 0 ? 0x11e : 0x114) + entity[0xd]);
		d2_ShowPrivilegMessage(buf, 0, 0x657c7);
		return 2;
	}
	if (*command == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) command + 0x14, (int) "%s", 0x1d84);
	}
	return 2;
}
