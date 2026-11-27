/* Owned (both targets) by src/GOLDTL.fcn_004f7890.c. */
extern char g_679060[];

int  __cdecl gm_HandleVerhoerMode2(void*, void*);
void __cdecl io_FormatTextBuffer(void*, int, ...);


/* ADDRESS: GOLDTL 0x004fa3b0 */
int __cdecl gm_HandleVerhoerMode2Privilege(void* obj, void* request)
{
	int r;

	r = 0;
	*(char*) ((char*) request + 0x14) = 0;
	if (*(int*) request != 3 && *(int*) request != 1) {
		return 1;
	}
	if ((*(unsigned int*) ((char*) obj + 0x1c8) & 0x100) != 0) {
		return 1;
	}
	if ((*(unsigned int*) ((char*) obj + 0x1cc) & 0x400) == 0) {
		return 1;
	}
	if (*(char*) ((char*) obj + 2) == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) "%s", 0x1e1c);
	}
	if ((*(unsigned int*) ((char*) obj + 0x1c8) & 0x200) != 0) {
		return 9;
	}
	if ((*(unsigned int*) ((char*) obj + 0x1c8) & 0x40000) != 0) {
		return 1;
	}
	if (*(int*) request == 3) {
		r = gm_HandleVerhoerMode2(obj, request);
	}
	return r | 2;
}
