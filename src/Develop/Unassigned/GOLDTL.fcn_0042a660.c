

int __cdecl msx_FindWaveDriverIndex(int);
typedef int (__stdcall* f)(int);

int __cdecl fcn_0042a660(int* input, int* out)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindWaveDriverIndex((int) input) >= 0) {
			*out = (*(f*) 0x6623ec)(*input);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
