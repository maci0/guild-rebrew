

#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl msx_FindWaveDriverIndex(char*);

int __cdecl fcn_0042b180(char* context)
{
	int i;
	int j;

	i = msx_FindWaveDriverIndex(context);
	if (i >= 0 && *(int*) (context + 0x14) < *(int*) (context + 0x18)) {
		for (j = 0; j < *(int*) (context + 0x18); j++) {
			if (g_6b7f50[i][j] == 0) {
				return j;
			}
		}
	}
	return -1;
}
