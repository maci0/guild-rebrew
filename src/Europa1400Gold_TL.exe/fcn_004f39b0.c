// FUNCTION: GOLDTL 0x4f5da0
// SIZE: 34

// fcn_004f39b0 — count slots [p]==1 with [p-0xf]==a.

int __cdecl fcn_004f39b0(int a)
{
	int p;
	int n;
	n = 0;
	for (p = 0x9a3825; p < 0x9a9225; p += 0x2d) {
		if (*(int*) (p - 0xf) == a && *(int*) p == 1) {
			n++;
		}
	}
	return n;
}
