

int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int, int, int);

int __cdecl msx_GetStreamMsPosition(int streamHandle, int outMsPos)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindStreamIndex(streamHandle) >= 0) {
			(*(f*) 0x66243c)(streamHandle, 0, outMsPos);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
