

int __cdecl msx_FindSampleHandleIndex(int);
typedef void (__stdcall* f)(int, int);

int __cdecl fcn_0042a920(int a1, int a2)
{
	int result = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(a1) >= 0) {
			(*(f*) 0x6623dc)(a1, a2);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
