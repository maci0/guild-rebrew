extern char g_665b88[];
extern char g_665b88[];



#include <math.h>

#pragma intrinsic(fabs, sqrt)

double __cdecl fcn_00502820(int x1, int y1, int x2, int y2)
{
	double dx;
	double dy;

	dx = fabs((double) x1 - (double) x2);
	dy = fabs((double) y1 - (double) y2);
	return sqrt(dx * dx + dy * dy) * *(double*) g_665b88;
}
