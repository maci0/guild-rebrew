

#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_0042b1c0(int key)
{
	int i;
	int j;

	for (i = 0; i < 0x10; i++) {
		if (g_6b7ed0[i] != 0) {
			for (j = 0; j < g_6b7ed0[i][6]; j++) {
				if (g_6b7f10[i][j] == key) {
					return j;
				}
			}
		}
	}
	return -1;
}
