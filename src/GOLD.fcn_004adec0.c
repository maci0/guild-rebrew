/* ADDRESS: GOLD 0x004adec0 */
void __cdecl fcn_004adec0(void)
{
	int n;
	int i;
	int *base;
	int needle;
	char *p;

	n = *(int *)0x600f40;
	i = 0;
	if (n <= 0)
		return;
	base = *(int **)0x600f48;
	needle = *(int *)0x6f0714;
	p = (char *)base;
loop:
	if (*(int *)p == needle)
		goto hit;
	i++;
	p += 0x2c;
	if (i < n)
		goto loop;
	return;
hit:
	*(int *)0x6f0710 = needle;
	if (i < n - 1)
		*(int *)0x6f0714 = base[(i + 1) * 11];
	else
		*(int *)0x6f0714 = -1;
}
