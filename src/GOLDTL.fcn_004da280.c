// FUNCTION: GOLDTL 0x4da280
// SIZE: 34

void __cdecl fcn_004e4aa0(int);

void __cdecl fcn_004da280(void)
{
	int a;
	int v;

	for (a = 0x9b0dc0; a < 0x9b0e00; a += 4) {
		v = *(int*) a;
		if (v != 0) {
			fcn_004e4aa0(v);
		}
	}
}
