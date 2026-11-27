typedef void (__stdcall* g_662408_f)(int);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern g_662408_f g_662408;
extern g_662408_f g_662408;




int __cdecl msx_FindStreamDriverIndex(int);
int __cdecl msx_FindStreamIndex(int);

int __cdecl msx_CloseStream(int streamId)
{
	int r = 0;
	int i;
	int j;

	if (g_6b7f90 != 0 && (i = msx_FindStreamDriverIndex(streamId)) >= 0 && (j = msx_FindStreamIndex(streamId)) >= 0) {
		g_662408(streamId);
		msx_WaveDrivers[i][5]--;
		g_6b7f50[i][j] = r;
	} else {
		r = -1;
	}
	return r;
}
