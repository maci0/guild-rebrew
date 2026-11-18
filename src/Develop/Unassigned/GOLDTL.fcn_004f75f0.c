


extern char g_679060[];

int __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl fcn_004f75f0(unsigned char* entity, int* request)
{
	char buf[0x100];

	if (*request != 3 && *request != 1) {
		return 1;
	}
	if (entity[0xd] > 3) {
		return 4;
	}
	if (entity[0xd] < 3) {
		return 1;
	}
	if (*request == 3 && entity[2] == 6) {
		io_FormatTextBuffer(buf, 0x1d5f, (entity[9] != 0 ? 0x11e : 0x114) + entity[0xd]);
		fcn_004fa5f0(buf, 0, 0x657c7);
		return 2;
	}
	if (*request == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) g_679060, 0x1d5e);
	}
	return 2;
}
