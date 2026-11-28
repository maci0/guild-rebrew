

#include "Develop/DieGildeAddOn/game/g_68e020.h"

extern Entry68e020 g_68e020[32];

int __cdecl gm_CountUnusedPresetCharacters(void)
{
	int n;
	unsigned int i;

	n = 0;
	for (i = 0; i < 32; i++) {
		if (g_68e020[i].state == 0) {
			n++;
		}
	}
	return n;
}
