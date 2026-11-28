


#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

/* ADDRESS: GOLDDE 0x004165f0 */
float __cdecl d3_Smoothstep(float lo, float hi, float x)
{
	float t;

	t = MIN(MAX((x - lo) / (hi - lo), 0.0f), 1.0f);
	return t * t * (3.0f - (t + t));
}
