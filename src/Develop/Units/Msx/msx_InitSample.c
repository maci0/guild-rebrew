__declspec(dllimport) void __stdcall AIL_init_sample(int);
extern char msx_Initialized[];


int __cdecl msx_FindSampleHandleIndex(int);
typedef void (__stdcall* AIL_INIT_SAMPLE_FN)(int);

/* ADDRESS: GOLDDE 0x00424ff0 */
int __cdecl msx_InitSample(int sampleHandle)
{
	int r = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindSampleHandleIndex(sampleHandle) >= 0) {
			AIL_init_sample(sampleHandle);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
