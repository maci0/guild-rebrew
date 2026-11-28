#include "Develop/Units/Msx/id_group.h"

extern IdGroup g_688118[];


/* ADDRESS: GOLDTL 0x004c2820 */
int __cdecl msx_FindGroupByKey(int key)
{
	int i;
	int j;

	i = 0;
	do {
		for (j = 0; g_688118[i].ids[j] != 0; j++) {
			if (g_688118[i].ids[j] == key)
				return i;
		}
	} while (g_688118[i++].ids[0] != 0);
	return -1;
}
