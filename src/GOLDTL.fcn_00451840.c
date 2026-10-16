#include <math.h>
#include "client_scene_transform.h"

/* ADDRESS: GOLD 0x00453e70 */
/* ADDRESS: GOLDTL 0x00451840 */
int __cdecl fcn_00451840(float* a, float* b, float eps)
{
	if (!(fabs(b[0] - a[0]) <= eps) || !(fabs(b[1] - a[1]) <= eps) || !(fabs(b[2] - a[2]) <= eps)) {
		return 0;
	}
	return 1;
}
