extern char g_679060[];

void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl d2_ShowExpelWorkerDialog(char*, int*);


/* ADDRESS: GOLDTL 0x004f95f0 */
int __cdecl gm_ObjExpelWorker(char* e, int* s)
{
	char* p;

	if (*s == 3 || *s == 1) {
		if (e[2] == 6)
			io_FormatTextBuffer((char*) s + 0x14, (int) "%s", 0x1ddb);
		if (e[0x166] != 0x16 && e[0x166] != 0x19)
			return 1;
		if (*(int*) (e + 0x1c8) & 0x200)
			return 9;
		if (*s == 3)
			d2_ShowExpelWorkerDialog(e, s);
		return 2;
	}
	if (*s == 4 || *s == 2) {
		if ((*(int*) (e + 0x1c8) & 0x100) == 0 || (p = *(char**) ((char*) s + 0x21c)) == 0)
			return 1;
		if (p[0x166] != 0x16 && p[0x166] != 0x19)
			return 1;
		if (*s == 4) {
			d2_ShowExpelWorkerDialog(e, s);
			return 10;
		}
		if (e[2] == 6)
			io_FormatTextBuffer((char*) s + 0x14, (int) "%s", 0x1ddb);
		return 10;
	}
	return 1;
}
