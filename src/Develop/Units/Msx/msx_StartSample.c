__declspec(dllimport) void __stdcall AIL_start_sample(int);
extern char msx_Initialized[];


int __cdecl msx_FindSampleHandleIndex(int);
typedef void (__stdcall* fcn_0042a7f0_f)(int);

/* ADDRESS: GOLDDE 0x00425020 */
int __cdecl msx_StartSample(int a1)
{
	int r = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindSampleHandleIndex(a1) >= 0) {
			AIL_start_sample(a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
