extern char g_774a80[];
extern char g_6b5c60[];
// FUNCTION: GOLD 0x005a8e90
// FUNCTION: GOLDTL 0x5b2310

void __cdecl fcn_0051af00(void*, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2310(void* a1)
{
	char t;

	t = *(char*) ((char*) a1 + 2);
	if (t == 6 || t == 7) {
		fcn_0051af00(g_774a80, 0x20be);
		fcn_00545d40(*(int*) ((char*) a1 + 4), -1, g_774a80, 0, 0x5fb, g_6b5c60);
	}
}
