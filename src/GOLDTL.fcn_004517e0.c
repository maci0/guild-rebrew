// FUNCTION: GOLD 0x453e10
// SIZE: 83
// FUNCTION: GOLDTL 0x4517e0
// SIZE: 83
// Hermite blend. The parentheses around the first two terms keep c2 from
// evaluating the third product first.

float __cdecl fcn_004517e0(float a, float b, float c, float d, float t)
{
	float t2;
	float t3;

	t2 = t * t;
	t3 = t * t2;
	return (a * (2.0f * t3 - 3.0f * t2 + 1.0f) + b * (3.0f * t2 - 2.0f * t3))
		+ c * (t3 - 2.0f * t2 + t) + d * (t3 - t2);
}
