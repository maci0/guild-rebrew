// FUNCTION: GOLDTL 0x42a880

int __cdecl fcn_0042b1c0(int);
typedef void (__stdcall* fcn_0042a880_f)(int);

int __cdecl fcn_0042a880(int a1)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b1c0(a1) >= 0) {
			(*(fcn_0042a880_f*) 0x6623d0)(a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
