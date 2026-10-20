int __cdecl fcn_00425bf0(int, int, int);

/* ADDRESS: GOLD 0x0040cfd0 */
int __cdecl fcn_0040cfd0(int *a)
{
	int e;
	int v;

	e = *a;
	if (e == 0) {
		fcn_00425bf0(*(int *)0x6332b8, *(int *)(*(int *)0x6332b8 + 0x118), 0x5f2254);
		return 0;
	}
	v = *(unsigned char *)(e + 0x8c);
	if (v & 0x10) {
		return 1;
	}
	return 0;
}
