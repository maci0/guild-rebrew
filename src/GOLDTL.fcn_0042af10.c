typedef int (__stdcall* g_662428_f)(int);
// GLOBAL: GOLDTL 0x662428
extern g_662428_f g_662428;
// GLOBAL: GOLD 0x5eb2ec
extern g_662428_f g_662428;
// FUNCTION: GOLD 0x0042c110
// SIZE: 41
// FUNCTION: GOLDTL 0x42af10
// SIZE: 41

extern int g_6b7f90;

int __cdecl fcn_0042b200(int);

int __cdecl fcn_0042af10(int a1)
{
	if (g_6b7f90 != 0) {
		if (fcn_0042b200(a1) >= 0) {
			return g_662428(a1);
		}
	}
	return -1;
}
