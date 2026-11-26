


#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl msx_ReacquireWaveDriver(int, int, int);

void __cdecl msx_ReacquireAllWaveDrivers(int a1, int a2)
{
	int driverCursor;

	if (g_6b7f90 != 0) {
		for (driverCursor = (int) msx_WaveDrivers; driverCursor < (int) (msx_WaveDrivers + 16); driverCursor += 4) {
			if (*(int*) driverCursor != 0) {
				msx_ReacquireWaveDriver(*(int*) driverCursor, a1, a2);
			}
		}
	}
}
