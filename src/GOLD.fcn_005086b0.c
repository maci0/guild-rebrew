
// fcn_005086b0 — sum [n+0xe] over iteration.

int __cdecl fcn_004ffe90(int, int, int, int);
int __cdecl fcn_004ffcc0(void);

int __cdecl fcn_005086b0(int a)
{
	int s;
	s = 0;
	do {
		char* n;
		n = (char*) fcn_004ffe90(a, 1, 4, 9);
		if (n == 0) {
			break;
		}
		s += *(int*) (n + 0xe);
	} while (fcn_004ffcc0() != 0);
	return s;
}
