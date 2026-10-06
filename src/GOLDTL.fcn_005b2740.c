extern char g_774a80[];
// GLOBAL: GOLDTL 0x6ab41c
extern char g_6ab41c[];
// FUNCTION: GOLD 0x005a92c0
// FUNCTION: GOLDTL 0x5b2740

void __cdecl fcn_0051af00(void*, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2740(void* a1, void* a2)
{
	char t;

	t = *(char*) ((char*) a2 + 2);
	if (t == 6 || t == 7) {
		fcn_0051af00(g_774a80, 0x20c6, *(unsigned short*) a1);
		fcn_00545d40(*(int*) ((char*) a2 + 4), -1, g_774a80, 0, 0x5fa, g_6ab41c);
	}
}
