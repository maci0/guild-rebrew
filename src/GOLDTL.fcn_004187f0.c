// FUNCTION: GOLD 0x00417270
// FUNCTION: GOLDTL 0x004187f0

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

float __cdecl fcn_004187f0(float lo, float hi, float x)
{
	float t;

	t = MIN(MAX((x - lo) / (hi - lo), 0.0f), 1.0f);
	return t * t * (3.0f - (t + t));
}
