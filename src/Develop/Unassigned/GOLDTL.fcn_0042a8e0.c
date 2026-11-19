

int __cdecl msx_FindSampleHandleIndex(int);
typedef int (__stdcall* f)(int);

int __cdecl fcn_0042a8e0(int a1, int* out)
{
	int result = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(a1) >= 0) {
			*out = (*(f*) 0x6623d8)(a1);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
