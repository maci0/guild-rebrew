int __cdecl fcn_0042c280(int);
typedef void (__stdcall *fcn_0042bd00_f)(int);

/* ADDRESS: GOLD 0x0042bd00 */
int __cdecl fcn_0042bd00(int a1)
{
	int r;

	r = 0;
	if (*(int *)0x6333b0 != 0) {
		if (fcn_0042c280(a1) >= 0) {
			(*(fcn_0042bd00_f *)0x5eb2fc)(a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
