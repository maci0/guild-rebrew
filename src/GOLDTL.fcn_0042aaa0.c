typedef int (__stdcall* g_662450_f)(int);
/* ADDRESS: GOLDTL 0x00662450 */
extern g_662450_f g_662450;
/* ADDRESS: GOLD 0x005eb34c */
extern g_662450_f g_662450;



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
