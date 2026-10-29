extern char g_774a80[];
char g_6ab570[24] = {
    0x5f, 0x4e, 0x41, 0x43, 0x48, 0x52, 0x49, 0x43, 0x48, 0x54, 0x45, 0x4e, 0x5f, 0x44, 0x4f, 0x4d,
    0x49, 0x5a, 0x49, 0x4c, 0x5f, 0x31, 0x32, 0x00,
};



void __cdecl fcn_0051af00(void*, int, void*, int);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);

void __cdecl fcn_005b3410(void* a1, void* a2, int a3)
{
	fcn_0051af00(g_774a80, 0x4070, a2, a3 + 0x4071);
	he_MessageBoxQuickjump(*(int*) ((char*) a1 + 4), -1, g_774a80, 1, 0x5ec,
	    *(int*) ((char*) a2 + 1), -1, 0, g_6ab570);
}
