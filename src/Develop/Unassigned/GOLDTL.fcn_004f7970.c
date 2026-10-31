


extern char g_679060[];

void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl fcn_004fa5f0(void*, int, int);

int __cdecl fcn_004f7970(void* a1, void* a2)
{
	char buf[0x200];
	int n;

	if (*(int*) a2 != 3 && *(int*) a2 != 1) {
		return 1;
	}
	if (*(unsigned char*) ((char*) a1 + 0xd) >= 6) {
		return 4;
	}
	if (*(unsigned char*) ((char*) a1 + 0xd) < 4) {
		return 1;
	}
	if (*(int*) a2 == 3 && *(char*) ((char*) a1 + 2) == 6) {
		n = (*(char*) ((char*) a1 + 9) ? 0x11e : 0x114) +
		    (*(unsigned char*) ((char*) a1 + 0xd) & 0xff);
		io_FormatTextBuffer(buf, 0x1d89, n);
		fcn_004fa5f0(buf, 1, 0x657c7);
		return 2;
	} else if (*(int*) a2 == 1 && *(char*) ((char*) a1 + 2) == 6) {
		io_FormatTextBuffer((char*) a2 + 0x14, (int) g_679060, 0x1d88);
	}
	return 2;
}
