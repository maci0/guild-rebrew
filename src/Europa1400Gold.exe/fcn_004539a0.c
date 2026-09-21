// FUNCTION: GOLD 0x004539a0
// SIZE: 57
// fcn_004539a0 — out = a + (b-a)*t (float 3-vector lerp).

void __cdecl fcn_004539a0(float* a, float* b, float t, float* out)
{
	int i;
	for (i = 0; i < 3; i++) {
		out[i] = a[i] + (b[i] - a[i]) * t;
	}
}
