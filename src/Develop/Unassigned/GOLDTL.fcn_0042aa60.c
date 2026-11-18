

int __cdecl fcn_0042b1c0(int);
typedef int (__stdcall* f)(int);

int __cdecl fcn_0042aa60(int a1, int* output)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b1c0(a1) >= 0) {
			*output = (*(f*) 0x006623f0)(a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
