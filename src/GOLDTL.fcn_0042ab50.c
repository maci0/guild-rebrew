

int __cdecl fcn_0042b1c0(int);
typedef int (__stdcall* f)(int, int);

int __cdecl fcn_0042ab50(int a1, int a2)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b1c0(a1) >= 0) {
			(*(f*) 0x006623fc)(a1, a2);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
