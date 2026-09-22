// FUNCTION: GOLDTL 0x546fb0
// SIZE: 38
// FUNCTION: GOLD 0x0040cd70
// SIZE: 42
// fcn_0040cd70 — count nodes with [n+0x88]==[0x5fb5b0].

int __cdecl fcn_0040cd70(void)
{
	int i;
	int n;
	int find;
	find = *(int*) 0x5fb5b0;
	n = 0;
	for (i = 0x1468ae0; i < 0x14696e0; i += 4) {
		int p;
		p = *(int*) i;
		if (p != 0 && *(int*) (p + 0x88) == find) {
			n++;
		}
	}
	return n;
}
