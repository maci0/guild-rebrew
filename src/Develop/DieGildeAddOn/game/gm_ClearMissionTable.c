

// fcn_004b39f0 — zeroes 0x1200 bytes at 0x10069a0, returns 1.

#include <string.h>

/* ADDRESS: GOLDDE 0x004a1e50 */
int __cdecl gm_ClearMissionTable(void)
{
	memset((void*) 0x10069a0, 0, 0x1200);
	return 1;
}
