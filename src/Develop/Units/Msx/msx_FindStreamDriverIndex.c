#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDTL 0x0042b280 */
int __cdecl msx_FindStreamDriverIndex(int id)
{
	int i;
	int j;

	for (i = 0; i < 16; i++) {
		if (msx_WaveDrivers[i] != 0) {
			for (j = 0; j < msx_WaveDrivers[i][6]; j++) {
				if (msx_StreamHandles[i][j] == id) {
					return i;
				}
			}
		}
	}
	return -1;
}
