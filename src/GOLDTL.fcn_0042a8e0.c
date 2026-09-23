// FUNCTION: GOLDTL 0x42a8e0
// SIZE: 54

int __cdecl fcn_0042b1c0(int);
typedef int (__stdcall* f)(int);

int __cdecl fcn_0042a8e0(int a1, int* out)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b1c0(a1) >= 0) {
			*out = (*(f*) 0x6623d8)(a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
