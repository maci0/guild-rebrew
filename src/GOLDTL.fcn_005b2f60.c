extern char g_774a80[];
/* ADDRESS: GOLDTL 0x006ab4d4 */
extern char g_6ab4d4[];


int __cdecl gm_RandomMod(int);
void __cdecl fcn_0051af00(void*, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2f60(void* a1)
{
	fcn_0051af00(g_774a80, 0x40a8, (gm_RandomMod(3) & 0xffff) + 0x40a9);
	fcn_00545d40(*(int*) ((char*) a1 + 4), -1, g_774a80, 1, 0x5fb, g_6ab4d4);
}
