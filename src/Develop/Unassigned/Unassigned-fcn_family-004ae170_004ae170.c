extern char g_7f4ca0[];

/* ADDRESS: GOLD 0x004ae030 */
/* ADDRESS: GOLDTL 0x004ae170 */
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

/* ADDRESS: GOLD 0x004ae120 */
/* ADDRESS: GOLDTL 0x004ae260 */
int __cdecl fcn_004ae260(int a1)
{
	int o;

	o = (a1 & 0xffff) * 540;
	if (*(unsigned short*) ((int) g_7f4ca0 + o) != 0xffff
	    && *(unsigned char*) ((int) g_7f4ca0 + 8 + o) > 0
	    && *(unsigned char*) ((int) g_7f4ca0 + 2 + o) == 0) {
		return 1;
	}
	return 0;
}
