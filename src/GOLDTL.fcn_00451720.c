// FUNCTION: GOLD 0x453d50
// SIZE: 188
// FUNCTION: GOLDTL 0x451720
// SIZE: 188

#include <math.h>

void __cdecl fcn_00451720(float* a, float* b, float* oa, float* ob)
{
	int k;
	float t;
	float d;
	float x;

	for (k = 0; k < 3; k++) {
		oa[k] = fmod(a[k], 6.2831855f);
		ob[k] = t = fmod(b[k], 6.2831855f);
		d = fabs(t - oa[k]);
		x = oa[k] + 6.2831855f;
		if (d > fabs(t - x)) {
			oa[k] = x;
		} else {
			x = oa[k] - 6.2831855f;
			if (d > fabs(t - x)) {
				oa[k] = x;
			}
		}
	}
}
