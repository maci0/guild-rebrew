// FUNCTION: GOLDTL 0x005e8de0
// SIZE: 99

int __cdecl fcn_005e8de0(float a, float b, float* out)
{
	float b2;

	if (a < 0.0f || b < 0.0f) {
		return 0;
	}
	out[0] = a;
	out[1] = b;
	b2 = b * b;
	out[2] = 6.2831855f * b2;
	out[3] = b2 * b * 4.1887903f;
	out[4] = out[3] * a;
	return 1;
}
