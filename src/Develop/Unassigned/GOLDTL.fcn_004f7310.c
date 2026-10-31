extern char s_679060[];

void __cdecl io_FormatTextBuffer(void* dst, void* fmt, ...);
void __cdecl fcn_004fa5f0(void* buf, int mode, int y);

/* ADDRESS: GOLDTL 0x004f7310 */
int __cdecl fcn_004f7310(char* a0, int* a1)
{
	char buf[0x100];
	int v;
	int r;

	v = *a1;
	if (v != 3 && v != 1) {
		return 1;
	}
	if (*(unsigned char*) (a0 + 0xd) >= 3) {
		return 4;
	}
	r = 2;
	if (v == 3 && *(char*) (a0 + 2) == 6) {
		io_FormatTextBuffer(buf, (void*) 0x1d34,
		    (*(char*) (a0 + 9) ? 10 : 0) + 0x114 + *(unsigned char*) (a0 + 0xd));
		fcn_004fa5f0(buf, 0, 0x657c7);
		return r;
	}
	if (v == 1 && *(char*) (a0 + 2) == 6) {
		io_FormatTextBuffer((char*) a1 + 0x14, s_679060, 0x1d33);
	}
	return r;
}
