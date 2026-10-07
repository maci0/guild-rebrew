typedef int (__stdcall* g_662450_f)(int);
// GLOBAL: GOLDTL 0x662450
extern g_662450_f g_662450;
// GLOBAL: GOLD 0x5eb34c
extern g_662450_f g_662450;
// FUNCTION: GOLD 0x0042be80
// FUNCTION: GOLDTL 0x42aaa0

extern int g_6b7f90;

int __cdecl fcn_0042b1c0(int);

int __cdecl fcn_0042aaa0(int a1)
{
	int r = -1;

	if (g_6b7f90 != 0 && fcn_0042b1c0(a1) >= 0) {
		r = g_662450(a1);
	}
	return r;
}
