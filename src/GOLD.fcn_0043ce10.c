/* ADDRESS: GOLD 0x0043ce10 */
void __cdecl fcn_0043ce10(unsigned char *a, int b)
{
	unsigned char *p;
	int i;

	*(int *)(a + 0x190) = 0;
	a[0x190] = 0xff;
	*(int *)(a + 0) = 0;
	*(int *)(a + 8) = 0;
	*(int *)(a + 4) = 0;
	*(int *)(a + 0xc) = 0;
	*(int *)(a + 0x10) = 0;
	*(int *)(a + 0x18) = b;
	p = a + 0x20;
	for (i = 3; i != 0; i--) {
		p[0x70] &= 0xfd;
		*(int *)(p + 0x64) = 0;
		*(int *)(p + 0) = 0;
		*(int *)(p + 4) = 0;
		*(int *)(p - 4) = 0;
		*(int *)(p + 0x68) = 0;
		p += 0x7c;
	}
}
