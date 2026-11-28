extern char str_fmt_s[];

void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_RunGegenspionageDialog(char*, int*);


/* ADDRESS: GOLDTL 0x004f91f0 */
int __cdecl gm_HandleSeniorGegenspionagePrivilege(char* e, int* s)
{
	char* p;

	if (*s == 3 || *s == 1) {
		if (e[2] == 6)
			io_FormatTextBuffer((char*) s + 0x14, (int) "%s", 0x1dc8);
		if (e[0x166] != 0xf && e[0x166] != 0x15 && e[0x166] != 0x1b)
			return 1;
		if (*(int*) (e + 0x1c8) & 0x200)
			return 9;
		if (*s == 3)
			d2_RunGegenspionageDialog(e, s);
		return 2;
	}
	if (*s == 4 || *s == 2) {
		if ((*(int*) (e + 0x1c8) & 0x100) == 0 || (p = *(char**) ((char*) s + 0x21c)) == 0)
			return 1;
		if (p[0x166] != 0xf && p[0x166] != 0x15 && p[0x166] != 0x1b)
			return 1;
		if (*s == 4) {
			d2_RunGegenspionageDialog(e, s);
			return 10;
		}
		if (e[2] == 6)
			io_FormatTextBuffer((char*) s + 0x14, (int) "%s", 0x1dc8);
		return 10;
	}
	return 1;
}
