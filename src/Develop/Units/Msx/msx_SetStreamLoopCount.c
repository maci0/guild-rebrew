__declspec(dllimport) int __stdcall AIL_set_stream_loop_count(int, int);
extern char msx_Initialized[];


int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int, int);

/* ADDRESS: GOLDDE 0x00425380 */
int __cdecl msx_SetStreamLoopCount(int streamHandle, int loopCount)
{
	int result = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindStreamIndex(streamHandle) >= 0) {
			AIL_set_stream_loop_count(streamHandle, loopCount);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
