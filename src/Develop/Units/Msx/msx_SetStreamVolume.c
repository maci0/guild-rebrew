__declspec(dllimport) int __stdcall AIL_set_stream_volume(int, int);
extern char msx_Initialized[];


int __cdecl msx_FindStreamIndex(int);
typedef int (__stdcall* f)(int, int);

/* ADDRESS: GOLDDE 0x00425340 */
int __cdecl msx_SetStreamVolume(int streamHandle, int volume)
{
	int r = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindStreamIndex(streamHandle) >= 0) {
			AIL_set_stream_volume(streamHandle, volume);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
