// FUNCTION: GOLDTL 0x42a5d0
// SIZE: 68

int __cdecl fcn_0042b1c0(int);
typedef int (__stdcall* fcn_0042a5d0_f)(int, int, int, int, int);

int __cdecl fcn_0042a5d0(int a1, int a2, int a3, int a4)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b1c0(a1) >= 0) {
			if ((*(fcn_0042a5d0_f*) 0x662398)(a1, a2, a3, a4, 0) == 0) {
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
