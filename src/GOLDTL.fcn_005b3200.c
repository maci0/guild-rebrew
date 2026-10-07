extern char g_774a80[];
extern char g_6ab540[];
// FUNCTION: GOLDTL 0x005b3200

void __cdecl fcn_0051af00(void*, int, void*, void*, int);
void __cdecl fcn_00545e80(int, int, void*, int, int, int, int, int, void*);

void __cdecl fcn_005b3200(void* a1, void* a2, void* a3, int a4)
{
	char t;

	t = *(char*) ((char*) a1 + 2);
	if (t == 6 || t == 7) {
		fcn_0051af00(g_774a80, 0x4077, (char*) a2 + 0x30, (char*) a2 + 0x40,
		    2 * a4 + 0x9a8);
		fcn_00545e80(*(int*) ((char*) a1 + 4), -1, g_774a80, 0, 0x5ec,
		    *(int*) ((char*) *(int*) ((char*) a2 + 0x16c) + 1),
		    *(int*) ((char*) a3 + 2), 0, g_6ab540);
	}
}
