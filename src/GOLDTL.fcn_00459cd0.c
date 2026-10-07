int __cdecl fcn_004346f0(char* a);

// FUNCTION: GOLDTL 0x459cd0
int __cdecl fcn_00459cd0(char* a)
{
	int r;

	r = 0;
	if (a != 0 && a[0x16a] == 0) {
		r = fcn_004346f0(a);
		a[0x16a] = 1;
	}
	return r;
}
