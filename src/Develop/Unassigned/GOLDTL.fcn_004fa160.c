/* Owned (both targets) by src/GOLDTL.fcn_004f7890.c. */
extern char g_679060[];

int  __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);


/* ADDRESS: GOLDTL 0x004fa160 */
int __cdecl fcn_004fa160(void* entity, void* request)
{
	char buf[0x100];

	if (*(int*) request != 3 && *(int*) request != 1) {
		return 1;
	}
	if ((*(unsigned int*) ((char*) entity + 0x1cc) & 0x800) == 0) {
		return 1;
	}
	if (*(int*) request == 3 && *(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer(buf, 0x1e14,
		    0x278 + (*(char*) ((char*) entity + 9) != 0 ? 0x28 : 0), 0x16b9);
		fcn_004fa5f0(buf, 0, 0x657c7);
		return 2;
	}
	if (*(int*) request == 1 && *(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer((char*) request + 0x14, (int) g_679060, 0x1e13);
	}
	return 2;
}
