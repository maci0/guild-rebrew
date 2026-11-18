

#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_0042b200(int key)
{
	int i;
	int j;

	for (i = 0; i < 0x10; i++) {
		if (msx_WaveDrivers[i] != 0) {
			for (j = 0; j < msx_WaveDrivers[i][6]; j++) {
				if (g_6b7f50[i][j] == key) {
					return j;
				}
			}
		}
	}
	return -1;
}
