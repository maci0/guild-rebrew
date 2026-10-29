int __cdecl fcn_005463a0(int, int, int);
int __cdecl he_fn_Handlung(void);

/* ADDRESS: GOLDTL 0x005b44b0 */
int __cdecl fcn_005b44b0(int* a1)
{
	int n;
	int v;

	n = 0;
	if (a1 != 0) {
		v = *(unsigned short*) a1;
	} else {
		v = 0xffff;
	}
	if (fcn_005463a0(1, 2, v) != 0) {
		do {
			n++;
		} while (he_fn_Handlung() != 0);
	}
	return n;
}
