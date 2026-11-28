


#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl msx_ReleaseSampleHandle(int);

/* ADDRESS: GOLDDE 0x00424f90 */
int __cdecl msx_ReleaseAllWaveSamples(void)
{
	int r = 0;
	int i;
	int j;

	if (msx_Initialized != 0) {
		for (i = 0; i < 0x10; i++) {
			if (msx_WaveDrivers[i] != 0) {
				for (j = 0; j < msx_WaveDrivers[i][6]; j++) {
					if (msx_SampleHandles[i][j] != 0 && msx_ReleaseSampleHandle(msx_SampleHandles[i][j]) == -1) {
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
