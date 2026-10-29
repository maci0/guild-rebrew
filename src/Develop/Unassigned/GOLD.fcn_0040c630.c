
// fcn_0040c630 — if(!*a) return 0; fcn_00406c60(*a, 2, *b); return 1.

int __cdecl fcn_00406c60(int, int, int);

int __cdecl fcn_0040c630(int* a, int* b)
{
	if (*a == 0) {
		return 0;
	}
	fcn_00406c60(*a, 2, *b);
	return 1;
}
