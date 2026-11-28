


#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl msx_ReleaseDigitalHandle(int);

/* ADDRESS: GOLDDE 0x00424d60 */
int __cdecl msx_ReleaseAllDrivers(void)
{
	int r = 0;
	int a;

	if (msx_Initialized != 0) {
		for (a = (int) msx_WaveDrivers; a < (int) (msx_WaveDrivers + 16); a += 4) {
			if (*(int*) a != 0 && msx_ReleaseDigitalHandle(*(int*) a) != 0) {
				r = -1;
			}
		}
	} else {
		r = -1;
	}
	return r;
}
