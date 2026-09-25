extern int g_6b7d7c;
// FUNCTION: GOLD 0x004272f0
// SIZE: 54
// FUNCTION: GOLDTL 0x423850
// SIZE: 54

int __cdecl fcn_0042a9a0(int, int);

int __cdecl fcn_00423850(int* a1, int a2)
{
	int r;

	r = g_6b7d7c;
	if (r != 0) {
		if (a1 != 0) {
			if (a2 >= 0 && a2 <= 0x7f) {
				if (a1[0xa] != a2) {
					a1[0xa] = a2;
					return fcn_0042a9a0(a1[0], a2);
				}
				return a2;
			}
			return a2;
		}
	}
	return r;
}
