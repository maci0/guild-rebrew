


#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDDE 0x004254b0 */
int __cdecl msx_FindFreeWaveDriver(void)
{
	int i;

	for (i = 0; i < 0x10; i++) {
		if (msx_WaveDrivers[i] == 0) {
			return i;
		}
	}
	return -1;
}
