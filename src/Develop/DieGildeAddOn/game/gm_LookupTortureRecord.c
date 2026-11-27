#include "g_664260.h"

extern Mult664260 g_664260[7];


/* ADDRESS: GOLDTL 0x00493f50 */
Mult664260* __cdecl gm_LookupTortureRecord(int key)
{
	int i;

	for (i = 0; i < 7; i++) {
		if (g_664260[i].key == key)
			return &g_664260[i];
	}
	return 0;
}
