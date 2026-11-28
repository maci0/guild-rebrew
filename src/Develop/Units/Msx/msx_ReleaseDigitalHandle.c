typedef int (__stdcall* g_662454_f)(int);
extern g_662454_f imp_AIL_digital_handle_release;
extern g_662454_f imp_AIL_digital_handle_release;



#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl msx_FindWaveDriverIndex(int);

int __cdecl msx_ReleaseDigitalHandle(int* audio)
{
	int r = 0;

	if (msx_Initialized != 0) {
		if (msx_FindWaveDriverIndex((int) audio) >= 0) {
			if (imp_AIL_digital_handle_release(*audio) == 0) {
				r = -1;
			}
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
