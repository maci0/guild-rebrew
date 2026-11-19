


extern char g_679060[];

int __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl fcn_004f7b20(unsigned char* obj, int* request)
{
	char buf[0x200];

	if (*request != 3 && *request != 1) {
		return 1;
	}
	if (obj[0xd] < 5) {
		return 1;
	}
	if (*request == 3 && obj[2] == 6) {
		io_FormatTextBuffer(buf, 0x1d8d, (obj[9] != 0 ? 0x11e : 0x114) + obj[0xd]);
		fcn_004fa5f0(buf, 0, 0x657c7);
		return 2;
	}
	if (*request == 1 && obj[2] == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1d8c);
	}
	return 2;
}
