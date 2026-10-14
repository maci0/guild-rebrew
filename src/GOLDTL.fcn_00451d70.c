


void __cdecl fcn_004518a0(float*);

void __cdecl fcn_00451d70(float* a, float* b, float* c, float* n)
{
	float dx;
	float dy;
	float dz;
	float e[4];

	dx = b[0] - a[0];
	dy = b[1] - a[1];
	dz = b[2] - a[2];
	e[0] = c[0] - a[0];
	e[1] = c[1] - a[1];
	e[2] = c[2] - a[2];
	n[0] = dy * e[2] - dz * e[1];
	n[1] = dz * e[0] - dx * e[2];
	n[2] = dx * e[1] - dy * e[0];
	fcn_004518a0(n);
}
