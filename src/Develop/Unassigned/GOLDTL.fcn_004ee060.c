#include "g_772f90.h"
extern ALCHEMY_DRAW_SLOT g_772f90[3];
extern ALCHEMY_DRAW_SLOT g_772f90[3];

/* ADDRESS: GOLD 0x004ec2d0 */
/* ADDRESS: GOLDTL 0x004ee060 */
char* __cdecl fcn_004ee060(int i)
{
	if (i < 0 || i >= 3) {
		return 0;
	}
	return (char*) g_772f90 + i * 24;
}
