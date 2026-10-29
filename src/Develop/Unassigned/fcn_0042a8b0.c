int __cdecl fcn_0042b1c0(int);

/* ADDRESS: GOLDTL 0x0042a8b0 */
int __cdecl fcn_0042a8b0(int a1, int a2)
{
	if (*(int*) 0x6b7f90 == 0) {
		return -1;
	}
	if (fcn_0042b1c0(a1) < 0) {
		return -1;
	}
	(*(void (__stdcall**) (int, int)) 0x6623d4)(a1, a2);
	return -1;
}
