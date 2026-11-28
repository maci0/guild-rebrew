typedef void (__stdcall* g_662408_f)(int);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern g_662408_f imp_AIL_close_stream;
extern g_662408_f imp_AIL_close_stream;




int __cdecl msx_FindStreamDriverIndex(int);
int __cdecl msx_FindStreamIndex(int);

int __cdecl msx_CloseStream(int streamId)
{
	int r = 0;
	int i;
	int j;

	if (msx_Initialized != 0 && (i = msx_FindStreamDriverIndex(streamId)) >= 0 && (j = msx_FindStreamIndex(streamId)) >= 0) {
		imp_AIL_close_stream(streamId);
		msx_WaveDrivers[i][5]--;
		msx_StreamHandles[i][j] = r;
	} else {
		r = -1;
	}
	return r;
}
