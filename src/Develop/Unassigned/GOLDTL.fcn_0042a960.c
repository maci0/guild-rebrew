

int __cdecl fcn_0042b1c0(int);
typedef int (__stdcall* f)(int);

int __cdecl fcn_0042a960(int key, int* out)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b1c0(key) >= 0) {
			*out = (*(f*) 0x6623e0)(key);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
