// FUNCTION: GOLDTL 0x42a4d0
// SIZE: 49

int __cdecl fcn_0042b2c0(void);
typedef void (__stdcall* f)(int, int);

int __cdecl fcn_0042a4d0(int a1)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b2c0() <= 1) {
			*(int*) 0x6b7f94 = a1;
			(*(f*) 0x66244c)(1, a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
