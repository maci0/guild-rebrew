// FUNCTION: GOLD 0x004ef330
// SIZE: 136
// FUNCTION: GOLDTL 0x004f1290
// SIZE: 136


int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);

float __cdecl fcn_004f1290(char* p)
{
	float v;

	v = 1.0f;
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x259)) {
		v = 1.05f;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x25b)) {
		v = v + 0.05f;
	}
	if (fcn_00502cd0(*(int*) (p + 0x5d), 2, 6, 0, 0x261)) {
		return v + 0.05f;
	}
	return v;
}
