

int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int, int);

int __cdecl msx_SetStreamPlaybackRate(int streamHandle, int rate)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindStreamIndex(streamHandle) >= 0) {
			(*(f*) 0x00662414)(streamHandle, rate);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
