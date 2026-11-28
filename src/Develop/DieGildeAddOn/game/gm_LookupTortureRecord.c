#include "g_664260.h"

extern Mult664260 gm_TortureMultipliers[7];


/* ADDRESS: GOLDTL 0x00493f50 */
/* ADDRESS: GOLDDE 0x00482d30 */
Mult664260* __cdecl gm_LookupTortureRecord(int key)
{
	int i;

	for (i = 0; i < 7; i++) {
		if (gm_TortureMultipliers[i].key == key)
			return &gm_TortureMultipliers[i];
	}
	return 0;
}
