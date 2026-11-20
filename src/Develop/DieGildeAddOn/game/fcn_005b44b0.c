int __cdecl he_StartHandlungSearch(int, int, int);
int __cdecl he_fn_Handlung(void);

/* ADDRESS: GOLDTL 0x005b44b0 */
int __cdecl fcn_005b44b0(int* filter)
{
	int n;
	int ok;

	n = 0;
	if (filter != 0)
		ok = he_StartHandlungSearch(1, 2, *(unsigned short*) filter);
	else
		ok = he_StartHandlungSearch(1, 2, 0xffff);
	if (ok != 0) {
		do {
			n++;
		} while (he_fn_Handlung() != 0);
	}
	return n;
}
