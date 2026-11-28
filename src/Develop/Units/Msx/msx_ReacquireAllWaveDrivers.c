


#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl msx_ReacquireWaveDriver(int, int, int);

/* ADDRESS: GOLDDE 0x00424df0 */
void __cdecl msx_ReacquireAllWaveDrivers(int window, int message)
{
	int driverCursor;

	if (msx_Initialized != 0) {
		for (driverCursor = (int) msx_WaveDrivers; driverCursor < (int) (msx_WaveDrivers + 16); driverCursor += 4) {
			if (*(int*) driverCursor != 0) {
				msx_ReacquireWaveDriver(*(int*) driverCursor, window, message);
			}
		}
	}
}
