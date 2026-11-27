typedef void (__stdcall* g_6623bc_f)(int);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern g_6623bc_f g_6623bc;
extern g_6623bc_f g_6623bc;




int __cdecl msx_FindSampleDriverIndex(int);
int __cdecl msx_FindSampleHandleIndex(int);

int __cdecl msx_ReleaseSampleHandle(int handle)
{
	int r = 0;
	int i;
	int j;

	if (g_6b7f90 != 0 && (i = msx_FindSampleDriverIndex(handle)) >= 0 && (j = msx_FindSampleHandleIndex(handle)) >= 0) {
		g_6623bc(handle);
		g_6b7f10[i][j] = r;
		msx_WaveDrivers[i][5]--;
	} else {
		r = -1;
	}
	return r;
}
