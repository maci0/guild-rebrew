/* ADDRESS: GOLD 0x0044f5f0 */
// fcn_0044f5f0 — accumulate and reset fields. (a=param2)

void __cdecl fcn_0044f5f0(int u, int* a)
{
	(void) u;
	a[0x1c / 4] += a[0x14 / 4];
	a[0x2c / 4] += a[0x24 / 4];
	a[0x14 / 4] = 0;
	a[0x24 / 4] = 0;
}
