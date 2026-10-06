extern char g_774a80[];
// GLOBAL: GOLDTL 0x6ab570
extern char g_6ab570[];
// FUNCTION: GOLD 0x005a9f90
// FUNCTION: GOLDTL 0x5b3410

void __cdecl fcn_0051af00(void*, int, void*, int);
void __cdecl fcn_00545e80(int, int, void*, int, int, int, int, int, void*);

void __cdecl fcn_005b3410(void* a1, void* a2, int a3)
{
	fcn_0051af00(g_774a80, 0x4070, a2, a3 + 0x4071);
	fcn_00545e80(*(int*) ((char*) a1 + 4), -1, g_774a80, 1, 0x5ec,
	    *(int*) ((char*) a2 + 1), -1, 0, g_6ab570);
}
