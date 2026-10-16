int __cdecl fcn_0042c2c0(int);
typedef void (__stdcall *F)(int, int, int);

/* ADDRESS: GOLD 0x0042c140 */
int __cdecl fcn_0042c140(int a1, int a2)
{
	int r;

	r = 0;
	if (*(int *)0x6333b0 != 0) {
		if (fcn_0042c2c0(a1) >= 0) {
			(*(F *)0x5eb2e8)(a1, r, a2);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
