


unsigned short __cdecl gm_RandomMod(int);

void __cdecl fcn_0058e4a0(int n, int* a, int* b, int base)
{
	int i;
	int v;

	for (i = 0; i < n; i += 2) {
		v = gm_RandomMod(3);
		b[i] = v;
		b[i + 1] = v;
		a[i] = v + base;
		a[i + 1] = b[i] + base + 3;
		base += 6;
	}
}
