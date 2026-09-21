// FUNCTION: GOLD 0x0042ec00
// SIZE: 32
// fcn_0042ec00 — if(!si) return 0; return fcn_005de784() % (si & 0xffff).

int __cdecl fcn_005de784(void);

int __cdecl fcn_0042ec00(int u1, int si, int u2)
{
	(void) u1; (void) u2;
	if (si == 0) {
		return 0;
	}
	return fcn_005de784() % (si & 0xffff);
}
