void __cdecl fcn_00463740(int, int, int);

/* ADDRESS: GOLD 0x00464fb0 */
int __cdecl fcn_00464fb0(int a)
{
	int n;
	int z;

	if (a != 0) {
		n = *(int *)(a + 0x1c);
		if (n != 0) {
			z = 0;
			*(int *)(a + 0x14) = z;
			*(int *)(a + 8) = z;
			*(int *)(a + 0x18) = z;
			*(int *)n = (*(int *)(n + 0xc) != 0) ? 7 : 0;
			fcn_00463740(*(int *)(*(int *)(a + 0x1c) + 0x14), a, 0);
			return 0;
		}
	}
	return -2;
}
