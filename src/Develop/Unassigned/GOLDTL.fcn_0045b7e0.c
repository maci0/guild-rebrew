typedef struct Cell {
	int kind;
	char pad_000[0x1c - 4];
} Cell;

/* ADDRESS: GOLDTL 0x0045b7e0 */
int __cdecl fcn_0045b7e0(int a0, int a1, int a2, int* a3, int* a4)
{
	Cell* base;
	Cell* e;
	int n;
	int i;
	int j;
	int lim;
	int d;
	int t;
	int hi;
	int lo;

	if (a0 == 0) {
		return 0;
	}
	base = *(Cell**) (a0 + 0x24);
	if (base == 0) {
		return 0;
	}
	if (a3 == 0) {
		return 0;
	}
	if (a4 == 0) {
		return 0;
	}
	n = *(int*) (a0 + 0x20);
	if (n <= 0) {
		return 0;
	}
	for (i = 0; i < n; i++) {
		lim = n - 1;
		if (i + a2 < lim) {
			lim = i + a2;
		}
		j = (a2 < 0) ? 0 : a2;
		for (; j <= lim; j++) {
			d = a2 - j;
			if (d < 0) {
				d = -d;
			}
			t = i - d;
			hi = n - 1;
			if (a1 + t < hi) {
				hi = a1 + t;
			}
			lo = a1 - t;
			if (lo < 0) {
				lo = 0;
			}
			for (; lo <= hi; lo++) {
				if (j < 0 || j >= n) {
					continue;
				}
				if (lo < 0 || lo >= n) {
					continue;
				}
				e = base + n * j + lo;
				if (e->kind == 0 || e->kind == 0xd) {
					continue;
				}
				*a3 = lo;
				*a4 = j;
				return 1;
			}
		}
	}
	return 0;
}
