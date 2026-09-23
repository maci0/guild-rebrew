// FUNCTION: GOLDTL 0x0042aa20
// SIZE: 64

int __cdecl fcn_0042b1c0(int);
typedef int (__stdcall* f)(int, int);

int __cdecl fcn_0042aa20(int a1, int a2)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b1c0(a1) >= 0) {
			(*(f*) 0x006623a4)(a1, a2);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
