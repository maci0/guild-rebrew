typedef int (__stdcall* g_662428_f)(int);
extern g_662428_f g_662428;
extern g_662428_f g_662428;



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
