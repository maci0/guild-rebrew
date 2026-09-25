// FUNCTION: GOLDTL 0x423960
// SIZE: 69

int __cdecl fcn_004246c0(void);
int __cdecl fcn_004246e0(void);
int __cdecl fcn_00424700(int);

int __cdecl fcn_00423960(void)
{
	int r = 0;
	int a;
	int b;
	int c;

	if (*(int*) 0x6b7d68 != 0) {
		a = fcn_004246c0();
		b = fcn_004246e0();
		c = fcn_00424700(0);
		r = (a + b) * 64 + (c + b + a + 0x1b) * 12 + *(int*) (*(char**) 0x6b7d68 + 0x34);
	}
	return r;
}
