extern int g_6b7d7c;



int __cdecl fcn_0042a920(int, int);

int __cdecl fcn_00423890(int* a1, int a2)
{
	int r;

	r = g_6b7d7c;
	if (r != 0) {
		if (a1 != 0) {
			if (a2 >= 0 && a2 <= 0x7f) {
				if (a1[9] != a2) {
					a1[9] = a2;
					return fcn_0042a920(a1[0], a2);
				}
				return a2;
			}
			return a2;
		}
	}
	return r;
}
