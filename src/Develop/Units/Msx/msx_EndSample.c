__declspec(dllimport) void __stdcall AIL_end_sample(int);
extern char msx_Initialized[];


int __cdecl msx_FindSampleHandleIndex(int);
typedef void (__stdcall* AIL_END_SAMPLE_FN)(int);

/* ADDRESS: GOLDDE 0x00425080 */
int __cdecl msx_EndSample(int sampleHandle)
{
	int r = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindSampleHandleIndex(sampleHandle) >= 0) {
			AIL_end_sample(sampleHandle);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
