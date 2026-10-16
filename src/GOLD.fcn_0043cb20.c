/* ADDRESS: GOLD 0x0043cb20 */
void __cdecl fcn_0043cb20(char *a, char *s)
{
	unsigned char old;
	char *p;

	p = a;
	old = *(unsigned char *)(s + 0x210);
	*(unsigned char *)(s + 0x210) = (unsigned char)((old & ~1) | ((*(int *)(p + 0x1f8) == 0) & 1));
	*(int *)(s + 0x1f8) = *(int *)(p + 0x1f8);
	while (*(int *)(p + 0x1f0) != 0)
		p = *(char **)(p + 0x1f0);
	*(char **)(p + 0x1f0) = s;
	*(char **)(s + 0x1f4) = p;
}
