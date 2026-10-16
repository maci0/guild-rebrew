/* ADDRESS: GOLD 0x00495fc0 */
// fcn_00495fc0 — if(a) return 0; return b ? 0 : 7.

int __cdecl fcn_00495fc0(int a, int u, int b)
{
	(void) u;
	if (a != 0) {
		return 0;
	}
	return (b == 0) ? 7 : 0;
}
