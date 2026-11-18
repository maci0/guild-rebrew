


#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_0042a390(int);

int __cdecl fcn_0042a3d0(void)
{
	int r = 0;
	int a;

	if (g_6b7f90 != 0) {
		for (a = (int) msx_WaveDrivers; a < (int) (msx_WaveDrivers + 16); a += 4) {
			if (*(int*) a != 0 && fcn_0042a390(*(int*) a) != 0) {
				r = -1;
			}
		}
	} else {
		r = -1;
	}
	return r;
}
