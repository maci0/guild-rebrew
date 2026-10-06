// FUNCTION: GOLD 0x004ae030
// FUNCTION: GOLDTL 0x4ae170

extern char g_7f4ca0[];

int __cdecl fcn_004ae170(int a1)
{
	unsigned char c;
	unsigned char f;

	a1 &= 0xffff;
	if (*(unsigned short*) (((unsigned char*)g_7f4ca0) + a1 * 540) != 0xffff) {
		c = (((unsigned char*)g_7f4ca0) + 8)[a1 * 540];
		if (c > 0) {
			f = (((unsigned char*)g_7f4ca0) + 2)[a1 * 540];
			if (f == 6 || f == 7 || f == 5) {
				return 1;
			}
		}
	}
	return 0;
}
