extern char g_774a80[];
extern char g_6b5c60[];
// FUNCTION: GOLD 0x005a8d50
// FUNCTION: GOLDTL 0x5b21d0

void __cdecl fcn_0051af00(void*, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b21d0(void* a1, void* a2, int a3)
{
	char t;

	t = *(char*) ((char*) a2 + 2);
	if (t == 6 || t == 7) {
		fcn_0051af00(g_774a80, 0x20ba, *(unsigned short*) a1, a3);
		fcn_00545d40(*(int*) ((char*) a2 + 4), -1, g_774a80, 0, 0x5ec, g_6b5c60);
	}
}
