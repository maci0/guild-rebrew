extern char g_679060[];

void __cdecl fcn_0051af00(void*, int, ...);
int __cdecl fcn_005d6c50(char*, int*);

/* ADDRESS: GOLD 0x004f6b40 */
/* ADDRESS: GOLDTL 0x004f8f30 */

int __cdecl fcn_004f8f30(char* e, int* s)
{
	int r;
	char* p;

	r = 0;
	if (*s == 3 || *s == 1) {
		if (e[2] == 6)
			fcn_0051af00((char*) s + 0x14, (int) g_679060, 0x1dc1);
		if (e[0x166] != 0xe)
			return 1;
		if (*(int*) (e + 0x1c8) & 0x200)
			return 9;
		if (*(int*) (e + 0x1c8) & 0x400000)
			return 1;
		if (*s == 3)
			r = fcn_005d6c50(e, s);
		return r | 2;
	}
	if (*s == 4 || *s == 2) {
		if ((*(int*) (e + 0x1c8) & 0x100) == 0 || (p = *(char**) ((char*) s + 0x21c)) == 0)
			return 1;
		if (p[0x166] != 0xe)
			return 1;
		if (*(int*) (p + 0x1c8) & 0x400000)
			return 1;
		if (*s == 4)
			r = fcn_005d6c50(e, s);
		else if (e[2] == 6)
			fcn_0051af00((char*) s + 0x14, (int) g_679060, 0x1dc1);
		return r | 10;
	}
	return 1;
}
