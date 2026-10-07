#include "g_772f90.h"
// GLOBAL: GOLDTL 0x772f90
extern Slot772f90 g_772f90[3];
// GLOBAL: GOLD 0x6f0de0
extern Slot772f90 g_772f90[3];
// FUNCTION: GOLD 0x004ec2d0
// FUNCTION: GOLDTL 0x4ee060

char* __cdecl fcn_004ee060(int i)
{
	if (i < 0 || i >= 3) {
		return 0;
	}
	return (char*) g_772f90 + i * 24;
}
