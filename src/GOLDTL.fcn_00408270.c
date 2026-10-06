// FUNCTION: GOLD 0x4076e0
// FUNCTION: GOLDTL 0x408270

int __cdecl fcn_00408270(float* a, float* b, int* ox, int* oy)
{
	float v[4];
	float s;

	v[0] = b[0] - a[0];
	v[2] = b[2] - a[2];
	s = 1.0f / a[4];
	v[0] = s * v[0];
	v[2] = s * v[2];
	*ox = (int) (v[0] + 0.5);
	*oy = (int) (v[2] + 0.5);
	return 1;
}
