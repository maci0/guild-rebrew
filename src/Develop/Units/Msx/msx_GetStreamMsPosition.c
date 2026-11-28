__declspec(dllimport) int __stdcall AIL_stream_ms_position(int, int, int);
extern char msx_Initialized[];


int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int, int, int);

/* ADDRESS: GOLDDE 0x00425430 */
int __cdecl msx_GetStreamMsPosition(int streamHandle, int outMsPos)
{
	int r = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindStreamIndex(streamHandle) >= 0) {
			AIL_stream_ms_position(streamHandle, 0, outMsPos);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
