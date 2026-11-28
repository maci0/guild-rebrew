/* Owned (both targets) by src/GOLDTL.fcn_004f7890.c. */
extern char str_fmt_s[];

int  __cdecl d2_ShowPrivilegMessage(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);


/* ADDRESS: GOLDTL 0x004fa2e0 */
/* ADDRESS: GOLDDE 0x004e60c0 */
int __cdecl gm_HandleHighRolePrivilege(void* entity, void* params)
{
	char buf[0x100];

	if (*(int*) params != 3 && *(int*) params != 1) {
		return 1;
	}
	if ((*(unsigned int*) ((char*) entity + 0x1cc) & 0x200) == 0) {
		return 1;
	}
	if (*(int*) params == 3 && *(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer(buf, 0x1e1b,
		    0x276 + (*(char*) ((char*) entity + 9) != 0 ? 0x28 : 0), 0x16ba);
		d2_ShowPrivilegMessage(buf, 0, 0x657c7);
		return 2;
	}
	if (*(int*) params == 1 && *(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer((char*) params + 0x14, (int) "%s", 0x1e1a);
	}
	return 2;
}
