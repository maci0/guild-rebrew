


extern char g_679060[];

int __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl fcn_004f9d80(unsigned char* entity, int* command)
{
	char buf[0x100];

	if (*command != 3 && *command != 1) {
		return 1;
	}
	if (entity[0xd] < 9) {
		return 1;
	}
	if (*command == 3 && entity[2] == 6) {
		io_FormatTextBuffer(buf, 0x1e06, (entity[9] != 0 ? 0x11e : 0x114) + entity[0xd]);
		fcn_004fa5f0(buf, 0, 0x657c7);
		return 2;
	}
	if (*command == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) command + 0x14, (int) "%s", 0x1e05);
	}
	return 2;
}
