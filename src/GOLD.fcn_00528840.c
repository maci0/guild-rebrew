int __cdecl fcn_0046bf00(int, int, int, int, int);
void __cdecl fcn_004760a0(int, int);
void __cdecl fcn_0046c250(int, int);

/* ADDRESS: GOLD 0x00528840 */
int __cdecl fcn_00528840(int a, int b, int c)
{
	int r;
	int off;

	r = fcn_0046bf00(a + 3, b, 0xc5, c, *(int *)0x6ed938);
	fcn_004760a0(r, 0x54);
	off = r * 187 * 4;
	*(int *)((char *)*(int *)0xf8f080 + off + 0x5c) = 1;
	fcn_0046c250(r, 0x60);
	return r;
}
