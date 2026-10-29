extern char g_679060[];

int __cdecl fcn_0051af00(char*, char*, int);
int __cdecl fcn_005dafd0(int, int);

/* ADDRESS: GOLDTL 0x004f9f70 */
int __cdecl fcn_004f9f70(int a, int b)
{
	int r;
	int v;

	v = *(int*) b;
	*(char*) (b + 0x14) = 0;
	r = 0;
	switch (v) {
	case 1:
	case 3:
		if ((*(int*) (a + 0x1cc) & 0x800) == 0) {
			return 1;
		}
		if (*(char*) (a + 2) == 6) {
			fcn_0051af00((char*) (b + 0x14), g_679060, 0x1e0d);
		}
		if (*(int*) (a + 0x1c8) & 0x200) {
			return 9;
		}
		if (*(int*) (a + 0x1cc) & 0x40000) {
			return 1;
		}
		if (v == 3) {
			r = fcn_005dafd0(a, b);
		}
		return r | 2;
	case 2:
	case 4:
		if ((*(int*) (a + 0x1c8) & 0x100) == 0) {
			return 1;
		}
		if (*(int**) (b + 0x21c) == 0) {
			return 1;
		}
		if ((*(int*) ((char*) *(int**) (b + 0x21c) + 0x1cc) & 0x800) == 0) {
			return 1;
		}
		if (*(int*) ((char*) *(int**) (b + 0x21c) + 0x1cc) & 0x40000) {
			return 1;
		}
		if (v == 4) {
			r = fcn_005dafd0(a, b);
		} else if (*(char*) (a + 2) == 6) {
			fcn_0051af00((char*) (b + 0x14), g_679060, 0x1e0d);
		}
		return r | 0xa;
	}
	return 1;
}
