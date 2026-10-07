// FUNCTION: GOLDTL 0x4cfa80

void __cdecl fcn_0046f280(int);

void __cdecl fcn_004cfa80(void)
{
	int a;
	int v;

	for (a = 0x9ba2e0; a < 0x9ba360; a += 4) {
		v = *(int*) a;
		if (v != -1) {
			fcn_0046f280(v);
			*(int*) a = -1;
		}
	}
}
