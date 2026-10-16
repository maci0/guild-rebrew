int __cdecl fcn_00423720(int a);
void __cdecl fcn_0041f7f0(int v);
void __cdecl fcn_0041f940(int n);

/* ADDRESS: GOLD 0x00423530 */
int __cdecl fcn_00423530(int a)
{
	int p;

	p = fcn_00423720(a);
	if (p != 0) {
		fcn_0041f7f0(p);
		fcn_0041f940(p);
		return 1;
	}
	return 0;
}
