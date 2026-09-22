// FUNCTION: GOLDTL 0x4732c0
// SIZE: 41

void __cdecl fcn_00473190(int, int);

void __cdecl fcn_004732c0(void)
{
	int a;
	int v;

	for (a = 0x1015ec0; a < 0x1015f40; a += 4) {
		v = *(int*) a;
		if (v != 0) {
			fcn_00473190(v, *(int*) 0x77250c);
		}
	}
}
