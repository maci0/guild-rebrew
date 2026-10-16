/* ADDRESS: GOLD 0x004675e0 */
void __cdecl fcn_004675e0(char* a)
{
	unsigned int sum_a;
	unsigned int sum_b;
	unsigned short* p;
	int n;
	int i;

	p = (unsigned short*) (a + 0x8c);
	sum_a = 0;
	sum_b = 0;
	n = 7;
	do {
		sum_a += *p;
		p += 2;
		n--;
	} while (n != 0);
	i = 0x80;
	p = (unsigned short*) (a + 0xa8);
	n = 0x79;
	do {
		sum_b += *p;
		p += 2;
		n--;
	} while (n != 0);
	if (i < 0x100) {
		n = 0x100 - i;
		p = (unsigned short*) (a + 0x8c + i * 4);
		do {
			sum_a += *p;
			p += 2;
			n--;
		} while (n != 0);
	}
	*(unsigned char*) (a + 0x1c) = (unsigned char) (sum_a <= (sum_b >> 2));
}
