typedef int (__stdcall* g_662428_f)(int);
extern g_662428_f imp_AIL_stream_status;
extern g_662428_f imp_AIL_stream_status;



#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl msx_FindStreamIndex(int);

int __cdecl msx_GetStreamStatus(int streamIdArg)
{
	if (msx_Initialized != 0) {
		if (msx_FindStreamIndex(streamIdArg) >= 0) {
			return imp_AIL_stream_status(streamIdArg);
		}
	}
	return -1;
}
