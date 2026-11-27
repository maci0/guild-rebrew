

int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int);

int __cdecl msx_GetStreamLoopCount(int streamHandle, int* output)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindStreamIndex(streamHandle) >= 0) {
			*output = (*(f*) 0x00662438)(streamHandle);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
