/* Owned (both targets) by src/GOLDTL.fcn_004f7890.c. */
extern char g_679060[];




void __cdecl io_FormatTextBuffer(void*, int, int);
void __cdecl fcn_004fa5f0(void*, int, int);

int __cdecl fcn_004f7cd0(void* entity, void* context)
{
	char buf[0x200];
	int n;

	if (*(int*) context != 3 && *(int*) context != 1) {
		return 1;
	}
	if (*(unsigned char*) ((char*) entity + 0xd) < 6) {
		return 1;
	}
	if (*(int*) context == 3 && *(char*) ((char*) entity + 2) == 6) {
		n = (*(char*) ((char*) entity + 9) ? 0x11e : 0x114) +
		    (*(unsigned char*) ((char*) entity + 0xd) & 0xff);
		io_FormatTextBuffer(buf, 0x1d93, n);
		fcn_004fa5f0(buf, 1, 0x657c7);
		return 2;
	} else if (*(int*) context == 1 && *(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer((char*) context + 0x14, (int) g_679060, 0x1d92);
	}
	return 2;
}
