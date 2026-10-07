extern char g_774a80[];
extern char g_6b5c60[];
extern unsigned short g_774970;
extern char g_7f4ca4[];
// FUNCTION: GOLD 0x005a9260
// FUNCTION: GOLDTL 0x5b26e0

void __cdecl fcn_0051af00(void*, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b26e0(void* a1, int a2)
{
	if (*(unsigned short*) a1 != *(unsigned short*) ((char*)&g_774970)) {
		fcn_0051af00(g_774a80, 0x20c5, *(unsigned short*) a1, a2);
		fcn_00545d40(*(int*) (g_7f4ca4 + 540 * *(unsigned short*) ((char*)&g_774970)),
		    -1, g_774a80, 0, 0x605, g_6b5c60);
	}
}
