__declspec(dllimport) int __stdcall AIL_pause_stream(int, int);
extern char msx_Initialized[];


int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int, int);

/* ADDRESS: GOLDDE 0x00425300 */
int __cdecl msx_PauseStream(int streamHandle, int paused)
{
	int r = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindStreamIndex(streamHandle) >= 0) {
			AIL_pause_stream(streamHandle, paused);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
