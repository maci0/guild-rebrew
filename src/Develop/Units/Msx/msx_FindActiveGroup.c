#include "Develop/Units/Msx/id_group.h"
extern IdGroup msx_LocationTrackGroups[];
extern IdGroup msx_LocationTrackGroups[];

/* ADDRESS: GOLD 0x004c1f90 */
/* ADDRESS: GOLDTL 0x004c27f0 */
int __cdecl msx_FindActiveGroup(void)
{
	int i;
	int v;
	char* p;

	i = 0;
	p = (char*) msx_LocationTrackGroups;
	do {
		if (p[0x112] != 0) {
			return i;
		}
		v = *(int*) p;
		i++;
		p += 0x114;
	} while (v != 0);
	return -1;
}
