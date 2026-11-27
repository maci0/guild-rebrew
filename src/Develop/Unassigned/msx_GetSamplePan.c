

int __cdecl msx_FindSampleHandleIndex(int);
typedef int (__stdcall* f)(int);

int __cdecl msx_GetSamplePan(int sampleHandle, int* out)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindSampleHandleIndex(sampleHandle) >= 0) {
			*out = (*(f*) 0x006623e8)(sampleHandle);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
