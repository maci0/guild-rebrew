extern char g_774a80[];
extern char g_6b5c60[];
// FUNCTION: GOLDTL 0x5b2d50
// SIZE: 94

void __cdecl fcn_0051af00(void*, int, int, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2d50(void* a1, int a2, int a3, int a4)
{
	char t;

	t = *(char*) ((char*) a1 + 2);
	if (t == 6 || t == 7) {
		fcn_0051af00(g_774a80, 0x4151, a2, a3, a3 != 1 ? 0x4153 : 0x4152, a4);
		fcn_00545d40(*(int*) ((char*) a1 + 4), -1, g_774a80, 0, 0x5fc, g_6b5c60);
	}
}
