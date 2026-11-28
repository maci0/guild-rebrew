


#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDDE 0x004254d0 */
int __cdecl msx_FindWaveDriverIndex(int a1)
{
	int i;

	for (i = 0; i < 0x10; i++) {
		if ((int) msx_WaveDrivers[i] == a1) {
			return i;
		}
	}
	return -1;
}
