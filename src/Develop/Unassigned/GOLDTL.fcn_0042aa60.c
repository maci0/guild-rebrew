

int __cdecl msx_FindSampleHandleIndex(int);
typedef int (__stdcall* f)(int);

int __cdecl msx_GetSampleLoopCount(int a1, int* output)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(a1) >= 0) {
			*output = (*(f*) 0x006623f0)(a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
