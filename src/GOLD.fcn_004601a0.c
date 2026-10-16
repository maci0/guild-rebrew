/* ADDRESS: GOLD 0x004601a0 */
void __cdecl fcn_004601a0(int obj, char flag)
{
	unsigned int i;
	unsigned int n;
	int p;
	int c;

	if (obj == 0)
		return;
	if (flag == 0 || *(int *)(obj + 0x70) <= 0 || *(unsigned char *)(obj + 0x71) != 0
		|| *(int *)(obj + 0x50) == -1) {
		(*(int *)(obj + 0x40))++;
		return;
	}
	p = *(volatile int *)0xfb9074;
	n = *(unsigned int *)0xfb9084;
	i = 0;
	if (n > 0) {
		p += 0x40;
		do {
			c = *(int *)p;
			if (c > 0 && *(int *)(p + 0x10) == *(int *)(obj + 0x50))
				*(int *)p = c + 1;
			n = *(unsigned int *)0xfb9084;
			i++;
			p += 0x80;
		} while (i < n);
	}
}
