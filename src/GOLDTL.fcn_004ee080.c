// FUNCTION: GOLD 0x4ec2f0
// FUNCTION: GOLDTL 0x4ee080

#include "g_772f90.h"

extern Slot772f90 g_772f90[3];

void __cdecl fcn_004ee080(Slot772f90* p)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (&g_772f90[i] == p) {
			g_772f90[i].active = 0;
			return;
		}
	}
}
