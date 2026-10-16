int __cdecl fcn_00425bf0(int, int, int);
int __cdecl fcn_00449690(int, int, int, int);

/* ADDRESS: GOLD 0x0040d010 */
int __cdecl fcn_0040d010(int *a, int *b)
{
	int e;

	e = *a;
	if (e == 0) {
		fcn_00425bf0(*(int *)0x6332b8, *(int *)(*(int *)0x6332b8 + 0x118), 0x5f227c);
		return 0;
	}
	return fcn_00449690(*(int *)(e + 0x34), 0x140, 0, *b);
}
