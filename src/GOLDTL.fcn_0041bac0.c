// FUNCTION: GOLDTL 0x0041bac0

extern int g_14ce86c;

unsigned int __cdecl fcn_0041bac0(int r, int g, unsigned char b)
{
	unsigned int c;

	c = 0xffffffff;
	if (g_14ce86c == 0x17) {
		c = (((r & 0xf8) << 5 | (g & 0xfc)) << 3) | (b >> 3);
	} else if (g_14ce86c == 0x18) {
		c = (((r & 0xf8) << 5 | (g & 0xf8)) << 2) | (b >> 3);
	} else if (g_14ce86c == 0x15) {
		c = ((((b << 8) | (unsigned char) g) << 8 | (r & 0xff)) << 8) | 0xff;
	} else if (g_14ce86c == 0x16) {
		c = (((b << 8) | (unsigned char) g) << 8 | (r & 0xff)) << 8;
	}
	return c;
}
