// FUNCTION: GOLD 0x00496070
// SIZE: 32
// fcn_00496070 — a ? 0 : (b == 0 ? 3 : 0).

int __cdecl fcn_00496070(int a, int u, int b)
{
	(void) u;
	if (a != 0) {
		return 0;
	}
	return (b == 0) ? 3 : 0;
}
