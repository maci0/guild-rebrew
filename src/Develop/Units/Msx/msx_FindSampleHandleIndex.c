

#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl msx_FindSampleHandleIndex(int key)
{
	int i;
	int j;

	for (i = 0; i < 0x10; i++) {
		if (msx_WaveDrivers[i] != 0) {
			for (j = 0; j < msx_WaveDrivers[i][6]; j++) {
				if (msx_SampleHandles[i][j] == key) {
					return j;
				}
			}
		}
	}
	return -1;
}
