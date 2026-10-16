int __cdecl fcn_0046c280(int, int, int, int, int);
int __cdecl fcn_00468ce0(int, int);

/* ADDRESS: GOLD 0x0046c380 */
int __cdecl fcn_0046c380(int a, int b, int c, int d, int e, int i)
{
	int base;
	int r;

	base = i * 964;
	r = fcn_0046c280(
		a + *(short *)(base + 0xf8f124),
		b + *(short *)(base + 0xf8f126),
		c,
		d,
		e);
	fcn_00468ce0(r, i);
	return r;
}
