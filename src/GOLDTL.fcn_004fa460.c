/* Owned (both targets) by src/GOLDTL.fcn_004f7890.c. */
extern char g_679060[];

int  __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl fcn_0051af00(void*, int, ...);

/* ADDRESS: GOLDTL 0x004fa460 */
/* ADDRESS: GOLD 0x004f8070 */

int __cdecl fcn_004fa460(void* a1, void* a2)
{
	char buf[0x100];

	if (*(int*) a2 != 3 && *(int*) a2 != 1) {
		return 1;
	}
	if ((*(unsigned int*) ((char*) a1 + 0x1cc) & 0x400) == 0) {
		return 1;
	}
	if (*(int*) a2 == 3 && *(char*) ((char*) a1 + 2) == 6) {
		fcn_0051af00(buf, 0x1e22,
		    0x277 + (*(char*) ((char*) a1 + 9) != 0 ? 0x28 : 0), 0x16bb);
		fcn_004fa5f0(buf, 0, 0x657c7);
		return 2;
	}
	if (*(int*) a2 == 1 && *(char*) ((char*) a1 + 2) == 6) {
		fcn_0051af00((char*) a2 + 0x14, (int) g_679060, 0x1e21);
	}
	return 2;
}
