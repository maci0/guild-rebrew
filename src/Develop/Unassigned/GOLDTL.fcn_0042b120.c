


#include "Develop/DieGildeAddOn/game/game_data.h"

int __cdecl fcn_0042b120(int a1)
{
	int i;

	for (i = 0; i < 0x10; i++) {
		if ((int) g_6b7ed0[i] == a1) {
			return i;
		}
	}
	return -1;
}
