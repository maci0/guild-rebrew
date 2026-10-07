// FUNCTION: GOLD 0x00495f90
// fcn_00495f90 — a ? 0 : (b == 0 ? 6 : 0).

int __cdecl fcn_00495f90(int a, int u, int b)
{
	(void) u;
	if (a != 0) {
		return 0;
	}
	return (b == 0) ? 6 : 0;
}
