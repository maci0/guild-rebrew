// FUNCTION: GOLDTL 0x477070
// SIZE: 43

void __cdecl fcn_00479cc0(int a, int b, int u, int d, char* e)
{
	(void) u;
	if (e == 0) {
		return;
	}
	*(int*) (e + 0x2c) = a;
	*(int*) (e + 0x34) = a + d;
	*(int*) (e + 0x30) = b;
	*(int*) (e + 0x38) = b + (int) e;
}
