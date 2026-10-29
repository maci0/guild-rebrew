extern char g_7f4ca0[];

int __cdecl fcn_004ffd90(int);
int __cdecl fcn_0050a7e0(int, int, int, int, int, int, int, int);
char* __cdecl fcn_00503e0(char*);
int __cdecl fcn_004fe470(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00500580 */
char* __cdecl fcn_00500580(unsigned char flags, int a2, int a3, int a4, int a5,
	char* a6)
{
	int i;
	char* rec;
	char* s;

	if (flags & 1) {
		i = fcn_004ffd90(a3) & 0xffff;
		if (i == 0xffff) {
			return 0;
		}
		if (flags & 2) {
			*(char*) (g_7f4ca0 + i * 0x21c + 0x165) = (char) a5;
			*(char*) (g_7f4ca0 + i * 0x21c + 0x164) = (char) a4;
		}
	} else {
		i = fcn_0050a7e0(a2, -1, -1, a3, 0, a4 & 0xff, a5 & 0xff, 2)
			& 0xffff;
	}
	if (i == 0xffff) {
		return 0;
	}
	rec = g_7f4ca0 + i * 0x21c;
	if (flags & 4) {
		if (a6 != 0) {
			s = fcn_00503e0(a6);
			if (s != 0) {
				fcn_004fe470(*(int*) (rec + 4), *(int*) (a6 + 1),
					*(int*) (s + 2), 0, 0);
			}
		}
	}
	return rec;
}
