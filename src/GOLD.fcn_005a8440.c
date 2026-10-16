void __cdecl fcn_004758e0(int);
void __cdecl fcn_0046e700(int);

/* ADDRESS: GOLD 0x005a8440 */
void __cdecl fcn_005a8440(int obj)
{
	int *p;
	int n;

	*(int *)0x6ed930 = *(int *)(obj + 0x27a8);
	fcn_004758e0(*(int *)obj);
	p = (int *)(obj + 0x18dc);
	for (n = 0x300; n != 0; n--) {
		if (*p != -1) {
			fcn_0046e700(*p);
			*p = -1;
		}
		p++;
	}
	*(int *)obj = -1;
}
