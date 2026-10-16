void __cdecl fcn_00425bf0(int, int, int);

/* ADDRESS: GOLD 0x0040ef40 */
int __cdecl fcn_0040ef40(int *slot, unsigned char *tag)
{
	int obj;
	int g;
	unsigned char cur;
	unsigned char t;

	obj = *slot;
	if (obj == 0) {
		g = *(int *)0x6332b8;
		fcn_00425bf0(g, *(int *)(g + 0x118), 0x5f2988);
		return 0;
	}
	cur = *(unsigned char *)(obj + 0x212);
	t = *tag;
	*(unsigned char *)(obj + 0x212) = (unsigned char)((cur & ~0x0c) | ((t << 2) & 0x0c));
	return 1;
}
