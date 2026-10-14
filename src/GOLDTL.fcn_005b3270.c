extern char g_774a80[];
extern char g_6ab558[];



void __cdecl fcn_0051af00(void*, int, void*, void*, void*);
void __cdecl fcn_00545e80(int, int, void*, int, int, int, int, int, void*);

void __cdecl fcn_005b3270(void* a1, int a2, void* a3)
{
	char t;

	t = *(char*) ((char*) a1 + 2);
	if (t == 6 || t == 7) {
		fcn_0051af00(g_774a80, 0x407a, (char*) a2 + 0x30, (char*) a2 + 0x40, a3);
		fcn_00545e80(*(int*) ((char*) a1 + 4), -1, g_774a80, 1, 0x5ec,
		    *(int*) ((char*) a3 + 1), -1, 0, g_6ab558);
	}
}
