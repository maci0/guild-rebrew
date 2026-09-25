// FUNCTION: GOLDTL 0x004ece30
// SIZE: 117

extern float g_6628a8;
extern float g_6628a0;
extern float g_665284;

float __cdecl fcn_004ec8a0(int p, int which);

float __cdecl fcn_004ece30(int p, int which, int* cap)
{
	float v;
	float d;
	int n;
	int m;

	v = fcn_004ec8a0(p, which);
	if (v < g_6628a8 || v >= g_6628a0) {
		return g_6628a8;
	}
	d = g_6628a0 - v;
	n = (int) (g_665284 * d);
	m = *cap < n ? *cap : n;
	*cap = m;
	return d * ((float) m / n);
}
