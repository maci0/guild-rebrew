typedef int (__stdcall* g_662450_f)(int);
extern g_662450_f imp_AIL_sample_status;
extern g_662450_f imp_AIL_sample_status;



#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl msx_FindSampleHandleIndex(int);

int __cdecl msx_GetSampleStatus(int sampleHandle)
{
	int r = -1;

	if (msx_Initialized != 0 && msx_FindSampleHandleIndex(sampleHandle) >= 0) {
		r = imp_AIL_sample_status(sampleHandle);
	}
	return r;
}
