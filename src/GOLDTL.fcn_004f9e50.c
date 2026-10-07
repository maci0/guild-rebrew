extern char g_679060[];

void __cdecl fcn_0051af00(void*, int, ...);
int __cdecl fcn_005dac90(char*, int*);

// FUNCTION: GOLD 0x004f7a60
// FUNCTION: GOLDTL 0x004f9e50

int __cdecl fcn_004f9e50(char* e, int* s)
{
	int r;
	char* p;

	r = 0;
	((char*) s)[0x14] = 0;
	if (*s == 3 || *s == 1) {
		if ((*(int*) (e + 0x1cc) & 0x800) == 0)
			return 1;
		if (e[2] == 6)
			fcn_0051af00((char*) s + 0x14, (int) g_679060, 0x1e07);
		if (*(int*) (e + 0x1c8) & 0x200)
			return 9;
		if (*(int*) (e + 0x1cc) & 0x80000)
			return 1;
		if (*s == 3)
			r = fcn_005dac90(e, s);
		return r | 2;
	}
	if (*s == 4 || *s == 2) {
		if ((*(int*) (e + 0x1c8) & 0x100) == 0 || (p = *(char**) ((char*) s + 0x21c)) == 0)
			return 1;
		if ((*(int*) (p + 0x1cc) & 0x800) == 0)
			return 1;
		if (*(int*) (p + 0x1cc) & 0x80000)
			return 1;
		if (*s == 4)
			r = fcn_005dac90(e, s);
		else if (e[2] == 6)
			fcn_0051af00((char*) s + 0x14, (int) g_679060, 0x1e07);
		return r | 10;
	}
	return 1;
}
