/* ADDRESS: GOLD 0x00479b50 */
// fcn_00479b50 — *(short*)(a[0x1c] + (a[0x10]*b + p)*2) = (short)c; return 1.

int __cdecl fcn_00479b50(int p, int b, short c, char* a)
{
	*(short*) (*(char**) (a + 0x1c) + (*(int*) (a + 0x10) * b + p) * 2) = c;
	return 1;
}
