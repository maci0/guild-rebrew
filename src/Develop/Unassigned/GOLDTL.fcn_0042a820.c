

int __cdecl msx_FindSampleHandleIndex(int);
typedef void (__stdcall* fcn_0042a820_f)(int);

int __cdecl msx_StopSample(int key)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(key) >= 0) {
			(*(fcn_0042a820_f*) 0x6623c8)(key);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
