// FUNCTION: GOLD 0x00495fc0
// fcn_00495fc0 — if(a) return 0; return b ? 0 : 7.

int __cdecl fcn_00495fc0(int a, int b, int u)
{
	(void) u;
	if (a != 0) {
		return 0;
	}
	return (b == 0) ? 7 : 0;
}
