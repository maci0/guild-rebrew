int __cdecl fcn_005463a0(int, int, int);
int __cdecl he_fn_Handlung(void);

/* ADDRESS: GOLDTL 0x005b44b0 */
int __cdecl fcn_005b44b0(int* a1)
{
	int n;
	int ok;

	n = 0;
	if (a1 != 0)
		ok = fcn_005463a0(1, 2, *(unsigned short*) a1);
	else
		ok = fcn_005463a0(1, 2, 0xffff);
	if (ok != 0) {
		do {
			n++;
		} while (he_fn_Handlung() != 0);
	}
	return n;
}
