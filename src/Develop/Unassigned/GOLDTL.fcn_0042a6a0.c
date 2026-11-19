typedef void (__stdcall* g_6623bc_f)(int);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern g_6623bc_f g_6623bc;
extern g_6623bc_f g_6623bc;




int __cdecl fcn_0042b240(int);
int __cdecl msx_FindSampleHandleIndex(int);

int __cdecl fcn_0042a6a0(int a1)
{
	int r = 0;
	int i;
	int j;

	if (g_6b7f90 != 0 && (i = fcn_0042b240(a1)) >= 0 && (j = msx_FindSampleHandleIndex(a1)) >= 0) {
		g_6623bc(a1);
		g_6b7f10[i][j] = r;
		msx_WaveDrivers[i][5]--;
	} else {
		r = -1;
	}
	return r;
}
