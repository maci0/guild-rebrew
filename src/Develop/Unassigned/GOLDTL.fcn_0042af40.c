

int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int);

int __cdecl msx_GetStreamPlaybackRate(int streamHandle, int* out)
{
	int result = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindStreamIndex(streamHandle) >= 0) {
			*out = (*(f*) 0x0066242c)(streamHandle);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
