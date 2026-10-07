// GLOBAL: GOLDTL 0x869480
extern char g_869480[0x300][0x300];
// GLOBAL: GOLD 0x7e5360
extern char g_869480[0x300][0x300];
// FUNCTION: GOLD 0x0050c520
// FUNCTION: GOLDTL 0x50f950

int __cdecl fcn_0050f950(int a1, int a2)
{
	if (a1 == a2) {
		return 0x7f;
	}
	return (signed char) *(char*) (((char*)g_869480) + a1 * 768 + a2);
}
