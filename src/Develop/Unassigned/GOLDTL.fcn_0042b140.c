

#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl fcn_0042b120(char*);

int __cdecl fcn_0042b140(char* audioDevice)
{
	int i;
	int j;

	i = fcn_0042b120(audioDevice);
	if (i >= 0 && *(int*) (audioDevice + 0x14) < *(int*) (audioDevice + 0x18)) {
		for (j = 0; j < *(int*) (audioDevice + 0x18); j++) {
			if (g_6b7f10[i][j] == 0) {
				return j;
			}
		}
	}
	return -1;
}
