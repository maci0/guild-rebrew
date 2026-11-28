#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDTL 0x0042b240 */
/* ADDRESS: GOLDDE 0x004255f0 */
int __cdecl msx_FindSampleDriverIndex(int id)
{
	int i;
	int j;

	for (i = 0; i < 16; i++) {
		if (msx_WaveDrivers[i] != 0) {
			for (j = 0; j < msx_WaveDrivers[i][6]; j++) {
				if (msx_SampleHandles[i][j] == id) {
					return i;
				}
			}
		}
	}
	return -1;
}
