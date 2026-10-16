int __cdecl fcn_0042c2c0(int);
typedef void (__stdcall *fcn_0042bfe0_f)(int);

/* ADDRESS: GOLD 0x0042bfe0 */
int __cdecl fcn_0042bfe0(int a1)
{
	int r;

	r = 0;
	if (*(int *) 0x6333b0 != 0) {
		if (fcn_0042c2c0(a1) >= 0) {
			(*(fcn_0042bfe0_f *) 0x5eb344)(a1);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
