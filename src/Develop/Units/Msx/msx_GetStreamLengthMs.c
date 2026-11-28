__declspec(dllimport) int __stdcall AIL_stream_ms_position(int, int, int);
extern char msx_Initialized[];


int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int, int, int);

/* ADDRESS: GOLDDE 0x00425470 */
int __cdecl msx_GetStreamLengthMs(int streamHandle, int outLengthMs)
{
	int result = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindStreamIndex(streamHandle) >= 0) {
			AIL_stream_ms_position(streamHandle, outLengthMs, 0);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
