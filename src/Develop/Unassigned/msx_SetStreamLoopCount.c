

int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int, int);

int __cdecl msx_SetStreamLoopCount(int streamHandle, int loopCount)
{
	int result = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (msx_FindStreamIndex(streamHandle) >= 0) {
			(*(f*) 0x00662420)(streamHandle, loopCount);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
