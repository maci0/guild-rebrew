int __cdecl fcn_0042c280(int);
typedef void (__stdcall *F)(int, int);

/* ADDRESS: GOLD 0x0042bdc0 */
int __cdecl fcn_0042bdc0(int a1, int a2)
{
	int r;

	r = 0;
	if (*(int *)0x6333b0 != 0) {
		if (fcn_0042c280(a1) >= 0) {
			(*(F *)0x5eb358)(a1, a2);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
