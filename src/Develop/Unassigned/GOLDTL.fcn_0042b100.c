


#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_0042b100(void)
{
	int i;

	for (i = 0; i < 0x10; i++) {
		if (msx_WaveDrivers[i] == 0) {
			return i;
		}
	}
	return -1;
}
