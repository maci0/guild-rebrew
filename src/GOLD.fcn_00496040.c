// FUNCTION: GOLD 0x00496040
// fcn_00496040 — a ? 0 : (b == 0 ? 2 : 0).

int __cdecl fcn_00496040(int a, int u, int b)
{
	(void) u;
	if (a != 0) {
		return 0;
	}
	return (b == 0) ? 2 : 0;
}
