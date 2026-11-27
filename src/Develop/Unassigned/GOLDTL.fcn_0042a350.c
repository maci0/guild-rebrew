#include "Develop/DieGildeAddOn/game/game_data.h"



int __cdecl msx_ReleaseWaveDriver(int);

int __cdecl msx_CloseAllWaveDrivers(void)
{
	int r = 0;
	int a;

	if (g_6b7f90 != 0) {
		for (a = (int) msx_WaveDrivers; a < (int) (msx_WaveDrivers + 16); a += 4) {
			if (*(int*) a != 0 && msx_ReleaseWaveDriver(*(int*) a) == -1) {
				r = -1;
			}
		}
	} else {
		r = -1;
	}
	return r;
}
