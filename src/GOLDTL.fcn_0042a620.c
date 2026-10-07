// FUNCTION: GOLDTL 0x42a620

int __cdecl fcn_0042b1c0(int);
typedef void (__stdcall* f)(int, int, int);

int __cdecl fcn_0042a620(int a1, int a2, int a3)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b1c0(a1) >= 0) {
			(*(f*) 0x6623a0)(a1, a2, a3);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
