typedef void (__stdcall* g_6623bc_f)(int);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern g_6623bc_f imp_AIL_release_sample_handle;
extern g_6623bc_f imp_AIL_release_sample_handle;




int __cdecl msx_FindSampleDriverIndex(int);
int __cdecl msx_FindSampleHandleIndex(int);

int __cdecl msx_ReleaseSampleHandle(int handle)
{
	int r = 0;
	int i;
	int j;

	if (msx_Initialized != 0 && (i = msx_FindSampleDriverIndex(handle)) >= 0 && (j = msx_FindSampleHandleIndex(handle)) >= 0) {
		imp_AIL_release_sample_handle(handle);
		msx_SampleHandles[i][j] = r;
		msx_WaveDrivers[i][5]--;
	} else {
		r = -1;
	}
	return r;
}
