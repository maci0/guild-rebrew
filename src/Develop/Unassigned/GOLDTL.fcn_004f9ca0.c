


extern char g_679060[];

int __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl fcn_004f9ca0(unsigned char* entity, int* context)
{
	char buf[0x100];

	if (*context != 3 && *context != 1) {
		return 1;
	}
	if (entity[0xd] > 8) {
		return 4;
	}
	if (entity[0xd] < 8) {
		return 1;
	}
	if (*context == 3 && entity[2] == 6) {
		io_FormatTextBuffer(buf, 0x1e04, (entity[9] != 0 ? 0x11e : 0x114) + entity[0xd]);
		fcn_004fa5f0(buf, 0, 0x657c7);
		return 2;
	}
	if (*context == 1 && entity[2] == 6) {
		io_FormatTextBuffer((char*) context + 0x14, (int) "%s", 0x1e03);
	}
	return 2;
}
