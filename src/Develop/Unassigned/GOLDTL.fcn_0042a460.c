


#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_0042a410(int, int, int);

void __cdecl fcn_0042a460(int a1, int a2)
{
	int driverCursor;

	if (g_6b7f90 != 0) {
		for (driverCursor = (int) msx_WaveDrivers; driverCursor < (int) (msx_WaveDrivers + 16); driverCursor += 4) {
			if (*(int*) driverCursor != 0) {
				fcn_0042a410(*(int*) driverCursor, a1, a2);
			}
		}
	}
}
