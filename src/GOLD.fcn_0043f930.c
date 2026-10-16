void __cdecl fcn_0043f990(void);
void __cdecl fcn_0043f910(int);

/* ADDRESS: GOLD 0x0043f930 */
void __cdecl fcn_0043f930(unsigned char c)
{
	int p;
	int s;

	if (c == *(unsigned char *)0x63373c)
		return;
	fcn_0043f990();
	p = *(int *)0x633738;
	*(unsigned char *)0x63373c = c;
	if (p != 0)
		fcn_0043f910(p);
	for (s = 0xfd7c4c; s < 0xfe744c; s += 0x3e0) {
		p = *(int *)s;
		if (p != 0 && p != *(int *)0x633738)
			fcn_0043f910(p);
	}
}
