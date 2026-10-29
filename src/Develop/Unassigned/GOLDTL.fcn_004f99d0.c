extern char g_679060[];

void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_005da820(char*, int*);


/* ADDRESS: GOLDTL 0x004f99d0 */
int __cdecl fcn_004f99d0(char* e, int* s)
{
	char* p;

	if (*s == 3 || *s == 1) {
		if (e[2] == 6)
			fcn_0051af00((char*) s + 0x14, (int) g_679060, 0x1dec);
		if (e[0x166] != 0x12 && e[0x166] != 0x16)
			return 1;
		if (*(int*) (e + 0x1c8) & 0x200)
			return 9;
		if (*s == 3)
			fcn_005da820(e, s);
		return 2;
	}
	if (*s == 4 || *s == 2) {
		if ((*(int*) (e + 0x1c8) & 0x100) == 0 || (p = *(char**) ((char*) s + 0x21c)) == 0)
			return 1;
		if (p[0x166] != 0x12 && p[0x166] != 0x16)
			return 1;
		if (*s == 4) {
			fcn_005da820(e, s);
			return 10;
		}
		if (e[2] == 6)
			fcn_0051af00((char*) s + 0x14, (int) g_679060, 0x1dec);
		return 10;
	}
	return 1;
}
