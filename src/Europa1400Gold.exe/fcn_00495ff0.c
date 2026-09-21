// FUNCTION: GOLD 0x00495ff0
// SIZE: 32
// fcn_00495ff0 — a ? 0 : (b == 0 ? 8 : 0).

int __cdecl fcn_00495ff0(int a, int u, int b)
{
	(void) u;
	if (a != 0) {
		return 0;
	}
	return (b == 0) ? 8 : 0;
}
