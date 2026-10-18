/* ADDRESS: GOLD 0x00460dd0 */
void __cdecl fcn_00460dd0(int obj)
{
	int base;
	unsigned int n;
	unsigned int i;
	int idx;
	int p;

	if ((*(unsigned char *)(obj + 0x68) & 2) != 0 || *(unsigned char *)obj == 0x2a)
		return;
	base = *(int *)0xfb9074;
	n = *(unsigned int *)0xfb9084;
	idx = (obj - base) >> 7;
	i = 0;
	if (n > 0) {
		p = base + 0x68;
		do {
			if (*(int *)(p - 0x28) > 0 && (*(unsigned char *)p & 2) != 0
				&& *(int *)(p - 0x1c) == idx) {
				*(int *)(p - 8) = *(int *)(obj + 0x60);
				*(int *)(p - 4) = *(int *)(obj + 0x64);
				*(int *)(p - 0x24) = *(int *)(obj + 0x44);
				*(int *)(p + 0xc) = *(int *)(obj + 0x74);
				*(int *)(p + 0x10) = *(int *)(obj + 0x78);
			}
			n = *(unsigned int *)0xfb9084;
			i++;
			p += 0x80;
		} while (i < n);
	}
}
