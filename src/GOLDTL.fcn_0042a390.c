// FUNCTION: GOLDTL 0x42a390
// SIZE: 54

int __cdecl fcn_0042b120(int);
typedef int (__stdcall* fcn_0042a390_f)(int);

int __cdecl fcn_0042a390(int* a1)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b120((int) a1) >= 0) {
			if ((*(fcn_0042a390_f*) 0x662454)(*a1) == 0) {
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
