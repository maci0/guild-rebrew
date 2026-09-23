// FUNCTION: GOLDTL 0x40c070
// SIZE: 40

void __cdecl fcn_004030e0(int);

void __cdecl fcn_0040c070(void)
{
	int a;
	int v;

	for (a = 0x14d0020; a < 0x14d0c20; a += 4) {
		v = *(int*) a;
		if (v != 0) {
			fcn_004030e0(v);
			*(int*) a = 0;
		}
	}
}
