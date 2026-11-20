


#include "g_772f90.h"

extern ALCHEMY_DRAW_SLOT g_772f90[3];

void __cdecl fcn_004ee080(ALCHEMY_DRAW_SLOT* p)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (&g_772f90[i] == p) {
			g_772f90[i].active = 0;
			return;
		}
	}
}
