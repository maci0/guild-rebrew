__declspec(dllimport) int __stdcall AIL_set_sample_loop_count(int, int);
extern char msx_Initialized[];


int __cdecl msx_FindSampleHandleIndex(int);
typedef int (__stdcall* f)(int, int);

/* ADDRESS: GOLDDE 0x00425130 */
int __cdecl msx_SetSampleLoopCount(int a1, int a2)
{
	int r = 0;

	if (*(int*) &msx_Initialized != 0) {
		if (msx_FindSampleHandleIndex(a1) >= 0) {
			AIL_set_sample_loop_count(a1, a2);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
