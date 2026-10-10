#include <math.h>

#pragma intrinsic(log10)

extern unsigned char g_773d75;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_0050b710(int a, unsigned char b);

// FUNCTION: GOLDTL 0x493e50
int __cdecl fcn_00493e50(unsigned short* a, unsigned short* b)
{
	int x;
	int y;
	double v;

	x = gm_WalkEntityChain(*a);
	y = gm_WalkEntityChain(*b);
	v = fcn_0050b710(y, g_773d75) + fcn_0050b710(x, g_773d75);
	if (10000.0 > v) {
		v = 10000.0;
	}
	v = v / (log10(v) + 1.0) * 0.05f;
	return (int) (v * 32);
}
