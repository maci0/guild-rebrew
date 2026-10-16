void __cdecl fcn_00402540(int);
void __cdecl fcn_00435740(int, int);

/* ADDRESS: GOLD 0x004059c0 */
void __cdecl fcn_004059c0(int s)
{
	int a;

	if ((*(unsigned char *)(s + 0x8c) & 0x10) == 0)
		return;
	if (*(int *)(s + 0x74) != 0) {
		if (*(int *)(*(int *)(s + 0x34) + 0x1cc) == 0)
			fcn_00402540(s);
		a = *(int *)(*(int *)(s + 0x74) + 0x68);
		if (a != 0)
			fcn_00435740(*(int *)(*(int *)(s + 0x34) + 0x1ec) + 0xf4, a);
		*(int *)(s + 0x74) = 0;
	}
	*(unsigned char *)(s + 0x8c) &= 0xef;
}
