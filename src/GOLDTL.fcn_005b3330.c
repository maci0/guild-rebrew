extern char g_774a80[];
extern char g_6ab558[];
// FUNCTION: GOLD 0x005a9eb0
// SIZE: 112
// FUNCTION: GOLDTL 0x5b3330
// SIZE: 112

void __cdecl fcn_0051af00(void*, int, void*, void*, void*, int);
void __cdecl fcn_00545e80(int, int, void*, int, int, int, int, int, void*);

void __cdecl fcn_005b3330(void* a1, void* a2, void* a3, void* a4)
{
	char t;

	t = *(char*) ((char*) a1 + 2);
	if (t == 6 || t == 7) {
		fcn_0051af00(g_774a80, 0x407c, (char*) a2 + 0x30, (char*) a2 + 0x40, a3,
		    2 * *(unsigned short*) a4 + 0x9a8);
		fcn_00545e80(*(int*) ((char*) a1 + 4), -1, g_774a80, 1, 0x5ec,
		    *(int*) ((char*) a3 + 1), *(int*) ((char*) a4 + 2), 0, g_6ab558);
	}
}
