#include "g_680bd0.h"
extern Entry680bd0 gm_MissionSpecs[48];
extern Entry680bd0 gm_MissionSpecs[48];

/* ADDRESS: GOLD 0x004b3ae0 */
/* ADDRESS: GOLDTL 0x004b3c50 */
char* __cdecl gm_LookupMissionSpec(int key)
{
	int i;
	int entry;

	for (i = 0, entry = (int) gm_MissionSpecs; entry < (int) gm_MissionSpecs + 0x540; entry += 0x1c, i++) {
		if (*(int*) entry == key) {
			return (char*) ((int) gm_MissionSpecs + i * 0x1c);
		}
	}
	return 0;
}
