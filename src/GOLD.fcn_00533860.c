int __cdecl fcn_0046bf00(int, int, int, int, int);
void __cdecl fcn_0046c250(int, int);

/* ADDRESS: GOLD 0x00533860 */
int __cdecl fcn_00533860(int a, int b, int c)
{
	int r;
	int off;

	r = fcn_0046bf00(0x20, a * 43 + 10, 0xbf, b, c);
	off = r * 187 * 4;
	*(int *)((char *)*(int *)0xf8f080 + off + 0x5c) = 1;
	fcn_0046c250(r, 0x12c);
	return r;
}
