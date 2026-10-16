int __cdecl fcn_00478fc0(int, int, int, int);

/* ADDRESS: GOLD 0x0047cad0 */
int __cdecl fcn_0047cad0(int a, int b, int c, int base, int key)
{
	unsigned char k;
	char *rec;
	unsigned char saved;

	k = (unsigned char)key;
	if (k > *(unsigned short *)(base + 0x2a))
		return 0;
	rec = (char *)(base + *(int *)(base + (int)k * 4 + 0x45));
	saved = *(unsigned char *)(rec + 0xd);
	*(unsigned char *)(rec + 0xd) = 3;
	fcn_00478fc0(a, b, c, base + *(int *)(base + (int)k * 4 + 0x45));
	*(unsigned char *)(rec + 0xd) = saved;
	return 1;
}
