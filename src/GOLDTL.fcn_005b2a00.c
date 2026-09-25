// GLOBAL: GOLDTL 0x774a80
extern char g_774a80[];
// GLOBAL: GOLDTL 0x6b5c60
extern char g_6b5c60[];
// FUNCTION: GOLD 0x005a9580
// SIZE: 61
// FUNCTION: GOLDTL 0x5b2a00
// SIZE: 61

void __cdecl fcn_0051af00(void*, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

void __cdecl fcn_005b2a00(void* a1, void* a2)
{
	fcn_0051af00(g_774a80, 0x1747, *(unsigned short*) a2);
	fcn_00545d40(*(int*) ((char*) a1 + 4), -1, g_774a80, 0, 0x5fa, g_6b5c60);
}
