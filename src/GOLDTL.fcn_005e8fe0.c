// FUNCTION: GOLDTL 0x005e8fe0
// SIZE: 254

float __cdecl gm_RandomFloat01(void);

int __cdecl fcn_005e8fe0(float* p, float spread, float* dir, float lift, float* up, float scale)
{
	float b[3];
	float a[3];
	float s;
	float t;
	float u;

	if (*(int*) (p + 25) != 0) {
		return 0;
	}
	s = (gm_RandomFloat01() * 1.5f - 1.0f) * scale + 1.0f;
	p[0] *= s;
	p[1] *= s;
	p[2] *= s;
	p[3] *= s;
	t = spread * ((gm_RandomFloat01() * 2.0f - 1.0f) * p[3]);
	a[0] = t * dir[0];
	a[1] = t * dir[1];
	a[2] = t * dir[2];
	u = lift * ((gm_RandomFloat01() * 2.0f - 1.0f) * p[3]) + 1.0f;
	b[0] = u * up[0];
	b[1] = u * up[1];
	b[2] = u * up[2];
	p[0] = b[0] + p[0] + a[0];
	p[1] = (b[1] + p[1]) + a[1];
	p[2] = (b[2] + p[2]) + a[2];
	p[4] = p[0];
	p[5] = p[1];
	p[6] = p[2];
	p[7] = p[3];
	return 1;
}
