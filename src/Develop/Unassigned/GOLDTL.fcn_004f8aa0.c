extern char g_679060[];

void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl gm_HandleBecircen(char*, int*);


/* ADDRESS: GOLDTL 0x004f8aa0 */
int __cdecl fcn_004f8aa0(char* e, int* s)
{
	char* p;

	if (*s == 3 || *s == 1) {
		if (e[2] == 6)
			io_FormatTextBuffer((char*) s + 0x14, (int) "%s", 0x1dad);
		if (e[0x166] != 0x16 && e[0x166] != 0x19 && e[0x166] != 0x12)
			return 1;
		if (*(int*) (e + 0x1c8) & 0x200)
			return 9;
		if (*s == 3)
			gm_HandleBecircen(e, s);
		return 2;
	}
	if (*s == 4 || *s == 2) {
		if ((*(int*) (e + 0x1c8) & 0x100) == 0 || (p = *(char**) ((char*) s + 0x21c)) == 0)
			return 1;
		if (p[0x166] != 0x16 && p[0x166] != 0x19 && p[0x166] != 0x12)
			return 1;
		if (*s == 4) {
			gm_HandleBecircen(e, s);
			return 10;
		}
		if (e[2] == 6)
			io_FormatTextBuffer((char*) s + 0x14, (int) "%s", 0x1dad);
		return 10;
	}
	return 1;
}
