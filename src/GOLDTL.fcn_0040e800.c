// FUNCTION: GOLDTL 0x40e800
// SIZE: 85

void __cdecl fcn_00442910(int, int*, float*, int);

void __cdecl fcn_0040e800(int* a1, int* a2, int* a3, int* a4)
{
	float a[3];
	int b[4];

	a[0] = 0.0f;
	a[1] = 0.0f;
	b[0] = *a1;
	b[1] = *a2;
	a[2] = 0.0f;
	b[2] = *a3;
	fcn_00442910(0, b, a, *a4);
}
