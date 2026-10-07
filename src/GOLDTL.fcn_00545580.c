// GLOBAL: GOLDTL 0x7d1d80
extern char g_7d1d80[];
// GLOBAL: GOLD 0x74df40
extern char g_7d1d80[];
// GLOBAL: GOLDTL 0x7dc440
extern char g_7dc440[];
// GLOBAL: GOLD 0x758600
extern char g_7dc440[];
// FUNCTION: GOLD 0x0053d860
// FUNCTION: GOLDTL 0x545580

int __cdecl fcn_00545580(int a1, int a2, int a3)
{
	if (a1 < 0 || a1 >= 0xa7) {
		return 1;
	}
	((int*) g_7d1d80)[a1] = a2;
	((int*) g_7dc440)[a1] = a3;
	return 0;
}
