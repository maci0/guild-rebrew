extern char g_679060[];

void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl fcn_005d7e80(char*, int*);


/* ADDRESS: GOLDTL 0x004f94e0 */
int __cdecl fcn_004f94e0(char* e, int* s)
{
	char* p;

	if (*s == 3 || *s == 1) {
		if (e[2] == 6)
			io_FormatTextBuffer((char*) s + 0x14, (int) g_679060, 0x1dd6);
		if (e[0x166] != 0x17 && e[0x166] != 0x13 && e[0x166] != 0x14 && e[0x166] != 0xd)
			return 1;
		if (*(int*) (e + 0x1c8) & 0x200)
			return 9;
		if (*s == 3)
			fcn_005d7e80(e, s);
		return 2;
	}
	if (*s == 4 || *s == 2) {
		if ((*(int*) (e + 0x1c8) & 0x100) == 0 || (p = *(char**) ((char*) s + 0x21c)) == 0)
			return 1;
		if (p[0x166] != 0x17 && p[0x166] != 0x13 && p[0x166] != 0x14 && p[0x166] != 0xd)
			return 1;
		if (*s == 4) {
			fcn_005d7e80(e, s);
			return 10;
		}
		if (e[2] == 6)
			io_FormatTextBuffer((char*) s + 0x14, (int) g_679060, 0x1dd6);
		return 10;
	}
	return 1;
}
