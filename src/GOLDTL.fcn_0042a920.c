// FUNCTION: GOLDTL 0x42a920

int __cdecl fcn_0042b1c0(int);
typedef void (__stdcall* f)(int, int);

int __cdecl fcn_0042a920(int a1, int a2)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b1c0(a1) >= 0) {
			(*(f*) 0x6623dc)(a1, a2);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
