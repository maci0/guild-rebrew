__declspec(dllimport) int __stdcall AIL_set_stream_ms_position(int, int);
extern char msx_Initialized[];


int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int, int);

/* ADDRESS: GOLDDE 0x004253c0 */
int __cdecl msx_SetStreamMsPosition(int streamHandle, int msPos)
{
	int r = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindStreamIndex(streamHandle) >= 0) {
			AIL_set_stream_ms_position(streamHandle, msPos);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
