// FUNCTION: GOLDTL 0x0042b000
// SIZE: 64

int __cdecl fcn_0042b200(int);
typedef int (__stdcall* f)(int);

int __cdecl fcn_0042b000(int a1, int* a2)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b200(a1) >= 0) {
			*a2 = (*(f*) 0x00662438)(a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
