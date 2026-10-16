int __cdecl fcn_005309d0(int, int);
int __cdecl fcn_005338d0(int, int, int);
void __cdecl fcn_005868d0(int);

/* ADDRESS: GOLD 0x00587960 */
void __cdecl fcn_00587960(int a)
{
	int r;
	int g;

	if (fcn_005309d0(0x587960, 0x67fff) == 0)
		return;
	do {
		r = fcn_005338d0(0x62a83c, *(int *)0x144a764, 0x16);
		g = *(int *)0x6f22e4;
		if (g != 0 && g == r)
			fcn_005868d0(a);
	} while (fcn_005309d0(0x587960, 0x67fff) != 0);
}
