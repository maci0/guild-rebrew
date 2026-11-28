__declspec(dllimport) int __stdcall AIL_set_sample_pan(int, int);
extern char msx_Initialized[];


int __cdecl msx_FindSampleHandleIndex(int);
typedef int (__stdcall* f)(int, int);

/* ADDRESS: GOLDDE 0x004250f0 */
int __cdecl msx_SetSamplePan(int sampleHandle, int pan)
{
	int r = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindSampleHandleIndex(sampleHandle) >= 0) {
			AIL_set_sample_pan(sampleHandle, pan);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
