void __cdecl io_FormatTextBuffer(void* out, int id, ...);
void __cdecl fcn_004fa5f0(void* buf, int a, char* b);

/* ADDRESS: GOLDTL 0x004fa090 */
int __cdecl fcn_004fa090(char* a0, int* a1)
{
	char buf[0x100];
	int* pa;
	int flags;
	char sep;

	pa = a1;
	if (*pa != 3 && *pa != 1) {
		return 1;
	}
	flags = *(int*) (a0 + 0x1cc);
	if (!(flags & 0x800)) {
		return 1;
	}
	sep = 6;
	if (*pa == 3) {
		if (*(unsigned char*) (a0 + 2) == sep) {
			io_FormatTextBuffer(buf, 0x1e12,
				*(unsigned char*) (a0 + 9) ? 0x2a0 : 0x278);
			fcn_004fa5f0(buf, 0, (char*) 0x657c7);
			return 2;
		}
	}
	if (*pa == 1) {
		if (*(unsigned char*) (a0 + 2) == sep) {
			io_FormatTextBuffer((char*) pa + 0x14, 0x679060, 0x1e11);
		}
	}
	return 2;
}
