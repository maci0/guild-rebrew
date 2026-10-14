extern char g_774a80[];
/* ADDRESS: GOLDTL 0x006ab4f0 */
extern char g_6ab4f0[];


int __cdecl gm_RandomMod(int);
void __cdecl fcn_0051af00(void*, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2fb0(void* a1)
{
	fcn_0051af00(g_774a80, 0x40ac, (gm_RandomMod(3) & 0xffff) + 0x40a9);
	fcn_00545d40(*(int*) ((char*) a1 + 4), -1, g_774a80, 1, 0x5fb, g_6ab4f0);
}
