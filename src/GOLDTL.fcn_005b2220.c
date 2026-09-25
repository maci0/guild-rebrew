extern char g_774a80[];
extern char g_6b5c60[];
// FUNCTION: GOLD 0x005a8da0
// SIZE: 84
// FUNCTION: GOLDTL 0x5b2220
// SIZE: 84

void __cdecl fcn_0051af00(void*, int, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2220(void* a1, void* a2, int a3, int a4)
{
	char t;

	t = *(char*) ((char*) a2 + 2);
	if (t == 6 || t == 7) {
		fcn_0051af00(g_774a80, 0x20bc, *(unsigned short*) a1, a3, a4);
		fcn_00545d40(*(int*) ((char*) a2 + 4), -1, g_774a80, 0, 0x5ff, g_6b5c60);
	}
}
