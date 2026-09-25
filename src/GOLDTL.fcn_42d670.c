// FUNCTION: GOLDTL 0x42d670
// SIZE: 60

int __cdecl fcn_0042d630(int);
int __cdecl fcn_0041ddd0(int);

void __cdecl fcn_0042d670(int a)
{
	int i;
	int x;
	i = fcn_0042d630(a);
	if (i == -1) {
		return;
	}
	x = *(int*) (0x149d188 + i * 29 * 4);
	fcn_0041ddd0(x);
	*(int*) (0x149d188 + i * 29 * 4) = 0;
}
