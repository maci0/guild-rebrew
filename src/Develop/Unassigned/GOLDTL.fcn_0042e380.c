

void __cdecl fcn_0042e260(int);

void __cdecl fcn_0042e380(void)
{
	int a;
	int v;

	for (a = 0x14d0020; a < 0x14d0c20; a += 4) {
		v = *(int*) a;
		if (v != 0) {
			fcn_0042e260(v);
		}
	}
}
