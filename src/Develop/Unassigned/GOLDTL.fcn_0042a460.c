


#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_0042a410(int, int, int);

void __cdecl fcn_0042a460(int a1, int a2)
{
	int a;

	if (g_6b7f90 != 0) {
		for (a = (int) msx_WaveDrivers; a < (int) (msx_WaveDrivers + 16); a += 4) {
			if (*(int*) a != 0) {
				fcn_0042a410(*(int*) a, a1, a2);
			}
		}
	}
}
