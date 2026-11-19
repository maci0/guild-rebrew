

int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int);

int __cdecl fcn_0042b000(int a1, int* output)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindStreamIndex(a1) >= 0) {
			*output = (*(f*) 0x00662438)(a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
