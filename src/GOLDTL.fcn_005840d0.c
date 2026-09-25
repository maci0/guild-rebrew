// FUNCTION: GOLDTL 0x005840d0
// SIZE: 134

void __cdecl fcn_005840d0(float* a, float* b, float* c, float* d, float t, float* out)
{
	float u;
	float u3;
	float t3;

	u = 1.0f - t;
	u3 = u * u * u;
	t3 = t * t * t;
	out[0] = (u * b[0] + t * c[0]) * u * t * 3.0f + u3 * a[0] + t3 * d[0];
	out[1] = (u * b[1] + t * c[1]) * u * t * 3.0f + u3 * a[1] + t3 * d[1];
}
