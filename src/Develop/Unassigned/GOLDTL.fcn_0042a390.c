typedef int (__stdcall* g_662454_f)(int);
extern g_662454_f g_662454;
extern g_662454_f g_662454;



#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl msx_FindWaveDriverIndex(int);

int __cdecl msx_ReleaseDigitalHandle(int* audio)
{
	int r = 0;

	if (g_6b7f90 != 0) {
		if (msx_FindWaveDriverIndex((int) audio) >= 0) {
			if (g_662454(*audio) == 0) {
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
