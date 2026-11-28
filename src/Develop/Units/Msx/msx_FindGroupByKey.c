#include "Develop/Units/Msx/id_group.h"

extern IdGroup msx_LocationTrackGroups[];


/* ADDRESS: GOLDTL 0x004c2820 */
/* ADDRESS: GOLDDE 0x004b0340 */
int __cdecl msx_FindGroupByKey(int key)
{
	int i;
	int j;

	i = 0;
	do {
		for (j = 0; msx_LocationTrackGroups[i].ids[j] != 0; j++) {
			if (msx_LocationTrackGroups[i].ids[j] == key)
				return i;
		}
	} while (msx_LocationTrackGroups[i++].ids[0] != 0);
	return -1;
}
