int __cdecl fcn_004a4410(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);

// FUNCTION: GOLDTL 0x496dc0
// SIZE: 145
int __cdecl fcn_00496dc0(float* o1, float* o2, int a3, char* e, int skip, int a6, int a7)
{
	float m;

	if (skip) {
		*o1 = -1.0e30f;
		*o2 = -1.0e30f;
		return 0;
	}
	*o1 = 0;
	*o2 = 0;
	if (e[0x167] && !e[0x166]) {
		m = 10.0f;
	} else {
		m = 1.0f;
	}
	fcn_004a4410(o1, o2, a3, e, 0, a6, a7);
	*o1 = m * *o1;
	*o2 = m * *o2;
	return 1;
}
