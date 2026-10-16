extern char g_774a80[];
/* ADDRESS: GOLDTL 0x006ab570 */
extern char g_6ab570[];



void __cdecl fcn_0051af00(void*, int, void*, int);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

void __cdecl fcn_005b3410(void* a1, void* a2, int a3)
{
	fcn_0051af00(g_774a80, 0x4070, a2, a3 + 0x4071);
	he_MessageBoxQuickjump(*(int*) ((char*) a1 + 4), -1, g_774a80, 1, 0x5ec,
	    *(int*) ((char*) a2 + 1), -1, 0, g_6ab570);
}
