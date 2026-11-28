extern char gm_MissionJobs[];
extern char gm_MissionJobs[];


/* fcn_004b3b60: zero 0x1200 bytes at g_10069a0; return 1. */
// (GOLDTL 0x10069a0 / GOLD 0xf82320.)

#include <string.h>

int __cdecl gm_ClearMissionJobs(void)
{
	memset(gm_MissionJobs, 0, 0x1200);
	return 1;
}
