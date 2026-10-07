void __cdecl fcn_005015e0(int* out, int a2, int a3, int id);
int __cdecl fcn_004a6550(int a1, int x);

// FUNCTION: GOLD 0x0048f1d0
// FUNCTION: GOLDTL 0x48e780
int __cdecl fcn_0048e780(int a1, char* a, char* b)
{
	int x;
	int y;

	if (a[0] != 4 || b[0] != 4) {
		return 0;
	}
	fcn_005015e0(&x, 0, 0, *(int*) (a + 4));
	if (!x) {
		return 0;
	}
	fcn_005015e0(&y, 0, 0, *(int*) (b + 4));
	if (!y) {
		return 0;
	}
	return fcn_004a6550(a1, x) ? 0x42 : 0;
}
