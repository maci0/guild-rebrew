


#include <math.h>

/* ADDRESS: GOLDDE 0x004475b0 */
void __cdecl d3_MatrixToEulerAngles(float* m, float* e)
{
	float c;

	c = (float)(sqrt(m[0] * m[0] + m[4] * m[4]));
	if (c > 1.9073486328125e-06) {
		e[0] = (float)(atan2(m[9], m[10]));
		e[1] = (float)(atan2(-m[8], c));
		e[2] = (float)(atan2(m[4], m[0]));
	} else {
		e[0] = (float)(atan2(-m[6], m[5]));
		e[1] = (float)(atan2(-m[8], c));
		e[2] = 0.0f;
	}
}
