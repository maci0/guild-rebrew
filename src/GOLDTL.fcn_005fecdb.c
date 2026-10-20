#pragma optimize("y", off)

typedef struct VTBL_FECDB VTBL_FECDB;
struct VTBL_FECDB {
	void* pad_000[0x90 / 4];
	int (__stdcall* m90)(void* obj, unsigned int a, int b, int c, int d,
		unsigned int flags, int f, int g, int h, int i);
};

/* ADDRESS: GOLDTL 0x005fecdb */
int __stdcall fcn_005fecdb(void* obj, unsigned int flags, int a3, int a4,
	int a5, int a6)
{
	unsigned int ecx;

	if ((flags & 0xe0fe2000u) == 0 && (flags & 1) == 0 && (flags & 0x400) == 0) {
		ecx = flags & 0x1cfff;
		if (ecx != 0) {
			if ((*(unsigned char*) ((char*) obj + 0x10) & 1) != 0) {
				ecx |= 1;
			}
		} else {
			ecx = *(unsigned int*) ((char*) obj + 0x10);
		}
		return (*(VTBL_FECDB**) obj)->m90(obj, ecx,
			*(int*) ((char*) obj + 0xc), *(int*) ((char*) obj + 0x2c), 0,
			flags, a3, a4, a5, a6);
	}
	return 0x8876086c;
}
