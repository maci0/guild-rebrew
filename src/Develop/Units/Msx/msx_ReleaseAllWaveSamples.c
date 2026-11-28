


#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl msx_ReleaseSampleHandle(int);

int __cdecl msx_ReleaseAllWaveSamples(void)
{
	int r = 0;
	int i;
	int j;

	if (g_6b7f90 != 0) {
		for (i = 0; i < 0x10; i++) {
			if (msx_WaveDrivers[i] != 0) {
				for (j = 0; j < msx_WaveDrivers[i][6]; j++) {
					if (g_6b7f10[i][j] != 0 && msx_ReleaseSampleHandle(g_6b7f10[i][j]) == -1) {
						r = -1;
					}
				}
			}
		}
	} else {
		r = -1;
	}
	return r;
}
