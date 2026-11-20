/* Owned (both targets) by src/GOLDTL.fcn_004f7890.c. */
extern char g_679060[];




void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl d2_ShowPrivilegMessage(void*, int, int);

int __cdecl fcn_004f7da0(void* entity, void* request)
{
	char buf[0x200];
	int n;

	if (*(int*) request != 3 && *(int*) request != 1) {
		return 1;
	}
	if (*(unsigned char*) ((char*) entity + 0xd) < 6) {
		return 1;
	}
	if (*(int*) request == 3 && *(char*) ((char*) entity + 2) == 6) {
		n = (*(char*) ((char*) entity + 9) ? 0x11e : 0x114) +
		    (*(unsigned char*) ((char*) entity + 0xd) & 0xff);
		io_FormatTextBuffer(buf, 0x1d95, n);
		d2_ShowPrivilegMessage(buf, 1, 0x657c7);
		return 2;
	} else if (*(int*) request == 1 && *(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1d94);
	}
	return 2;
}
