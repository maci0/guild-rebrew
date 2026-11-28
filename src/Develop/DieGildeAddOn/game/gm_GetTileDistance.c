extern char dbl_2_9081633[];
extern char dbl_2_9081633[];



#include <math.h>

#pragma intrinsic(fabs, sqrt)

/* ADDRESS: GOLDDE 0x004ede60 */
double __cdecl gm_GetTileDistance(int x1, int y1, int x2, int y2)
{
	double dx;
	double dy;

	dx = fabs((double) x1 - (double) x2);
	dy = fabs((double) y1 - (double) y2);
	return sqrt(dx * dx + dy * dy) * *(double*) dbl_2_9081633;
}
