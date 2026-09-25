// FUNCTION: GOLDTL 0x005b1f10
// SIZE: 213

extern char* g_774a78;

int __cdecl fcn_00430910(void*, int, int, int);

int __cdecl fcn_005b1f10(int fh)
{
	int n;
	char* p;
	int i;

	n = 0;
	for (p = g_774a78; p != 0; n++) {
		p = *(char**) (p + 0x48);
	}
	if (fcn_00430910(&n, 4, 1, fh) == 0) {
		return 0;
	}
	for (p = g_774a78; p != 0; p = *(char**) (p + 0x48)) {
		if (fcn_00430910(p, 4, 1, fh) == 0) {
			return 0;
		}
		if (fcn_00430910(p + 4, 4, 1, fh) == 0) {
			return 0;
		}
		if (fcn_00430910(p + 0x44, 4, 1, fh) == 0) {
			return 0;
		}
		for (i = 0; i < 7; i++) {
			if (fcn_00430910(p + 0xc + i * 8, 4, 1, fh) == 0) {
				return 0;
			}
			if (fcn_00430910(p + 0x10 + i * 8, 1, 1, fh) == 0) {
				return 0;
			}
		}
	}
	return 1;
}
