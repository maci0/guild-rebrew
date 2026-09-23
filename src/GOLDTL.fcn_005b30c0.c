extern char g_774a80[];
// GLOBAL: GOLDTL 0x6ab50c
extern char g_6ab50c[];
// FUNCTION: GOLDTL 0x5b30c0
// SIZE: 83

void __cdecl fcn_0051af00(void*, int, int, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b30c0(void* a1, void* a2, void* a3)
{
	fcn_0051af00(g_774a80, 0x40af, 0x40a3, *(unsigned short*) a2,
	             *(int*) ((char*) a2 + 0x16c), *(unsigned short*) a3);
	fcn_00545d40(*(int*) ((char*) a1 + 4), -1, g_774a80, 0, 0x5fa, g_6ab50c);
}
