// FUNCTION: GOLD 0x0043b670
// fcn_0043b670 — set bits; return 1.

int __cdecl fcn_0043b670(char* a, int b)
{
	a[0x210] |= 4;
	if (b != 0) {
		a[0x212] &= 0x7f;
	}
	a[0x213] &= 0xfe;
	return 1;
}
