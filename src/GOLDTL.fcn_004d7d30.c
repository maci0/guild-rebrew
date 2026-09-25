// GLOBAL: GOLDTL 0x772ea8
extern int g_772ea8;
// GLOBAL: GOLD 0x6f0cf8
extern int g_772ea8;
// GLOBAL: GOLDTL 0x772eac
extern int g_772eac;
// GLOBAL: GOLD 0x6f0cfc
extern int g_772eac;
// FUNCTION: GOLD 0x004d6930
// SIZE: 51
// FUNCTION: GOLDTL 0x4d7d30
// SIZE: 51

void __cdecl fcn_004d7d30(char* p)
{
	if (g_772ea8 != 0) {
		*(int*) (p + 0x354) = 0;
		*(int*) (p + 0x358) = g_772eac;
		return;
	}
	*(int*) (p + 0x354) = 1;
}
