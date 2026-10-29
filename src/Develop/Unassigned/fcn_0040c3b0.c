#include <math.h>

extern int g_14cb8ec;

/* ADDRESS: GOLDTL 0x0040c3b0 */
float __cdecl fcn_0040c3b0(float* value)
{
	float result;

	result = (float) sin(*value);
	g_14cb8ec = *(int*) (&result);
	return result;
}
