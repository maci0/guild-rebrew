// FUNCTION: GOLDTL 0x43c1d0
// SIZE: 234

char __cdecl fcn_0043c140(int*, int, int, int);

void __cdecl fcn_0043c1d0(int* a)
{
	unsigned char div[3];
	int k;
	int d;
	int m;
	int i;
	int j;

	div[0] = 1;
	div[1] = 2;
	div[2] = 4;
	for (k = 0; k < 3; k++) {
		d = div[k];
		m = a[0] / d;
		for (j = 0; j < m; j++) {
			for (i = 0; i < m; i++) {
				if (fcn_0043c140(a, i * d, j * d, d)) {
					((unsigned char*) a[9 + k])[j * m + i] |= 0x40;
				} else {
					((unsigned char*) a[9 + k])[j * m + i] &= 0xbf;
				}
			}
		}
	}
	((unsigned char*) a)[0x8036] |= 1;
}
