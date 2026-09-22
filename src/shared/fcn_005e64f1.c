// FUNCTION: GOLD 0x005e64f1
// SIZE: 43
// fcn_005e64f1 — strnlen.

int __cdecl fcn_005e64f1(char* a, int n)
{
	char* p;
	int k;
	p = a;
	for (k = n; k != 0; k--) {
		if (*p == 0) {
			return (int) (p - a);
		}
		p++;
	}
	return n;
}
