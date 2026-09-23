// GLOBAL: GOLDTL 0x7f4ca0
extern char g_7f4ca0[];
// GLOBAL: GOLD 0x770b80
extern char g_7f4ca0[];
// GLOBAL: GOLDTL 0x774800
extern char g_774800[];
// GLOBAL: GOLD 0x6f2448
extern char g_774800[];
// FUNCTION: GOLD 0x004ce170
// SIZE: 59
// FUNCTION: GOLDTL 0x4cef70
// SIZE: 59

int __cdecl fcn_004cef70(int a1, char* a2)
{
	int r;

	r = 0;
	if (*(int*) (a2 + 0x16c) == (int) (g_7f4ca0 + a1 * 540)) {
		r = 0x800;
	}
	if (*(int*) g_774800 != 0) {
		r = 0x800;
	}
	return r;
}
