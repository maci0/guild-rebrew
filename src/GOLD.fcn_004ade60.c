/* ADDRESS: GOLD 0x004ade60 */
void __cdecl fcn_004ade60(void)
{
	int n;
	int i;
	int *base;
	int needle;
	char *p;

	n = *(int *)0x600f44;
	i = 0;
	if (n <= 0)
		return;
	base = *(int **)0x600f4c;
	needle = *(int *)0x6f071c;
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
	*(int *)0x6f0718 = needle;
	if (i < n - 1)
		*(int *)0x6f071c = base[(i + 1) * 11];
	else
		*(int *)0x6f071c = -1;
}
