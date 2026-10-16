void __cdecl fcn_0043f300(int);
void __cdecl fcn_0043f990(void);

/* ADDRESS: GOLD 0x0043f8a0 */
void __cdecl fcn_0043f8a0(unsigned int a)
{
	unsigned int n;
	unsigned int c;
	unsigned char hi;

	if (a > 0x100 || a < 4)
		return;
	if (a > 0x40)
		n = 0x40;
	else
		n = a;
	c = 0;
	while ((n & 1) == 0) {
		n >>= 1;
		c++;
	}
	*(unsigned char *)0x633751 = 2;
	*(int *)0x633748 = 1 << c;
	hi = (unsigned char)(a >> 7);
	*(unsigned char *)0x633750 = (unsigned char)(6 - c);
	if (hi <= 2)
		*(unsigned char *)0x633751 = hi;
	fcn_0043f300(0xfc0d60);
	fcn_0043f990();
}
