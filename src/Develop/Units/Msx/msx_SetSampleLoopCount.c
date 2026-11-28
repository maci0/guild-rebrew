

int __cdecl msx_FindSampleHandleIndex(int);
typedef int (__stdcall* f)(int, int);

int __cdecl msx_SetSampleLoopCount(int a1, int a2)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(a1) >= 0) {
			(*(f*) 0x006623a4)(a1, a2);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
