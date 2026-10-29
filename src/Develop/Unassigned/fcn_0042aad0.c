int __cdecl fcn_0042b1c0(int);
typedef void (__stdcall* f)(int, int, int);

/* ADDRESS: GOLDTL 0x0042aad0 */
int __cdecl fcn_0042aad0(int a1, int a2)
{
	int r = 0;

	if (*(int*) 0x6b7f90 != 0) {
		if (fcn_0042b1c0(a1) >= 0) {
			(*(f*) 0x6623f4)(a1, a2, 0);
		} else {
			r = -1;
		}
	} else {
		r = -1;
	}
	return r;
}
