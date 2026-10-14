

void __cdecl fcn_00473150(int);

void __cdecl fcn_004732f0(void)
{
	int a;
	int v;

	for (a = 0x1015ec0; a < 0x1015f40; a += 4) {
		v = *(int*) a;
		if (v != 0) {
			fcn_00473150(v);
			*(int*) a = 0;
		}
	}
}
