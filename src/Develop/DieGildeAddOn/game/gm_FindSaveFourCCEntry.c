#include "Develop/DieGildeAddOn/game/g_68e020.h"

extern Entry68e020 g_68e020[32];

/* ADDRESS: GOLDTL 0x004ef000 */
int* __cdecl gm_FindSaveFourCCEntry(int id)
{
	unsigned int i;

	for (i = 0; i < 0x20; i++) {
		if (g_68e020[i].key == id)
			return (int*) &g_68e020[i];
	}
	return 0;
}
