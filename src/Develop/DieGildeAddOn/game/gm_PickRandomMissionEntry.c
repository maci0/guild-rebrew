#include "g_680bd0.h"

extern Entry680bd0 gm_MissionSpecs[48];

int __cdecl gm_CountMissionEntriesByKey(int);
int __cdecl gm_MissionRandomMod(int);


/* ADDRESS: GOLDTL 0x004b3db0 */
/* ADDRESS: GOLDDE 0x004a20a0 */
int __cdecl gm_PickRandomMissionEntry(int key)
{
	int n;
	int pick;
	int i;
	int seen;

	n = gm_CountMissionEntriesByKey(key);
	if (n > 0) {
		pick = gm_MissionRandomMod(n);
		for (i = 0, seen = 0; i < 48; i++) {
			if (gm_MissionSpecs[i].key == key)
				seen++;
			if (seen > pick)
				return gm_MissionSpecs[i].f0;
		}
	}
	return 0xff;
}
