/* ADDRESS: GOLD 0x00460a90 */
void __cdecl fcn_00460a90(unsigned char *s, unsigned char *p, unsigned char *q)
{
	unsigned char a;
	unsigned char c;

	if (s != 0 && p != 0 && q != 0) {
		a = s[0x68];
		c = (unsigned char)(s[0x72] & 0x0f);
		c = (unsigned char)(c + c);
		c = (unsigned char)(c | (a & 0x20));
		c = (unsigned char)(c + c);
		c = (unsigned char)(c | ((a >> 3) & 2));
		c = (unsigned char)(c | (a & 1));
		*p = c;
		*q = (unsigned char)((s[0x6a] & 0x1f) | (unsigned char)(s[0x69] << 4));
	}
}
