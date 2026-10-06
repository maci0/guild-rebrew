/* Owned (both targets) by src/GOLDTL.fcn_004f7890.c. */
extern char g_679060[];

// FUNCTION: GOLDTL 0x4f7cd0
// FUNCTION: GOLD 0x4f58e0

void __cdecl fcn_0051af00(void*, int, int);
void __cdecl fcn_004fa5f0(void*, int, int);

int __cdecl fcn_004f7cd0(void* a1, void* a2)
{
	char buf[0x200];
	int n;

	if (*(int*) a2 != 3 && *(int*) a2 != 1) {
		return 1;
	}
	if (*(unsigned char*) ((char*) a1 + 0xd) < 6) {
		return 1;
	}
	if (*(int*) a2 == 3 && *(char*) ((char*) a1 + 2) == 6) {
		n = (*(char*) ((char*) a1 + 9) ? 0x11e : 0x114) +
		    (*(unsigned char*) ((char*) a1 + 0xd) & 0xff);
		fcn_0051af00(buf, 0x1d93, n);
		fcn_004fa5f0(buf, 1, 0x657c7);
		return 2;
	} else if (*(int*) a2 == 1 && *(char*) ((char*) a1 + 2) == 6) {
		fcn_0051af00((char*) a2 + 0x14, (int) g_679060, 0x1d92);
	}
	return 2;
}
