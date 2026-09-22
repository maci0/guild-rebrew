// FUNCTION: GOLD 0x0044e570
// SIZE: 34
// fcn_0044e570 — (popcount32(a) == 1).

int __cdecl fcn_0044e570(int a)
{
	int i;
	int n;
	n = 0;
	for (i = 0; i < 0x20; i++) {
		n += a & 1;
		a >>= 1;
	}
	return n == 1;
}
