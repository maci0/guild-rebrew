// GLOBAL: GOLDTL 0x665b88
extern char g_665b88[];
// GLOBAL: GOLD 0x5ee8e0
extern char g_665b88[];
// FUNCTION: GOLD 0x004ffc90
// SIZE: 43
// FUNCTION: GOLDTL 0x502820
// SIZE: 43

#include <math.h>

#pragma intrinsic(fabs, sqrt)

double __cdecl fcn_00502820(int a1, int a2, int a3, int a4)
{
	double dx;
	double dy;

	dx = fabs((double) a1 - (double) a3);
	dy = fabs((double) a2 - (double) a4);
	return sqrt(dx * dx + dy * dy) * *(double*) g_665b88;
}
