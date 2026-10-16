void __cdecl fcn_00460e40(int, int);

/* ADDRESS: GOLD 0x00461130 */
unsigned char __cdecl fcn_00461130(int s)
{
	int p;

	if (s == 0)
		return 0;
	if (*(unsigned char *)0x633450 == 0)
		return 0;
	if ((*(unsigned char *)(s + 0x68) & 2) != 0)
		return 0;
	p = *(int *)(s + 0x60);
	if (p != 0) {
		*(int *)0x146356c = ((int (__stdcall *)(int))(*(int **)p)[2])(p);
		*(int *)(s + 0x60) = 0;
	}
	p = *(int *)(s + 0x64);
	if (p != 0) {
		*(int *)0x146356c = ((int (__stdcall *)(int))(*(int **)p)[2])(p);
		*(int *)(s + 0x64) = 0;
	}
	if (*(int *)(s + 0x4c) != 0 && *(unsigned char *)s != 0x2a)
		fcn_00460e40(s, 0);
	return 0;
}
