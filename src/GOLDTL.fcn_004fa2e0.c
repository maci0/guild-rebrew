/* Owned (both targets) by src/GOLDTL.fcn_004f7890.c. */
extern char g_679060[];

int  __cdecl fcn_004fa5f0(void*, int, int);
void __cdecl fcn_0051af00(void*, int, ...);

// FUNCTION: GOLDTL 0x4fa2e0
// SIZE: 208
// FUNCTION: GOLD 0x4f7ef0
// SIZE: 208

int __cdecl fcn_004fa2e0(void* a1, void* a2)
{
	char buf[0x100];

	if (*(int*) a2 != 3 && *(int*) a2 != 1) {
		return 1;
	}
	if ((*(unsigned int*) ((char*) a1 + 0x1cc) & 0x200) == 0) {
		return 1;
	}
	if (*(int*) a2 == 3 && *(char*) ((char*) a1 + 2) == 6) {
		fcn_0051af00(buf, 0x1e1b,
		    0x276 + (*(char*) ((char*) a1 + 9) != 0 ? 0x28 : 0), 0x16ba);
		fcn_004fa5f0(buf, 0, 0x657c7);
		return 2;
	}
	if (*(int*) a2 == 1 && *(char*) ((char*) a1 + 2) == 6) {
		fcn_0051af00((char*) a2 + 0x14, (int) g_679060, 0x1e1a);
	}
	return 2;
}
