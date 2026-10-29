typedef int (__stdcall* g_662398_f)(int, int, int, int, int);
extern g_662398_f g_662398;
extern g_662398_f g_662398;



extern int g_6b7f90;

int __cdecl fcn_0042b1c0(int);

int __cdecl fcn_0042a5d0(int a1, int a2, int a3, int a4)
{
	int r = 0;

	if (g_6b7f90 != 0) {
		if (fcn_0042b1c0(a1) >= 0) {
			if (g_662398(a1, a2, a3, a4, 0) == 0) {
				r = -1;
			}
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
