__declspec(dllimport) void __stdcall AIL_set_sample_volume(int, int);
extern char msx_Initialized[];


int __cdecl msx_FindSampleHandleIndex(int);
typedef void (__stdcall* f)(int, int);

/* ADDRESS: GOLDDE 0x004250b0 */
int __cdecl msx_SetSampleVolume(int sampleHandle, int volume)
{
	int result = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindSampleHandleIndex(sampleHandle) >= 0) {
			AIL_set_sample_volume(sampleHandle, volume);
		} else {
			result = -1;
		}
	} else {
		result = -1;
	}
	return result;
}
