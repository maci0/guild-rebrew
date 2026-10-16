int __cdecl fcn_004644b0(int, int);

/* ADDRESS: GOLD 0x00465000 */
int __cdecl fcn_00465000(int s)
{
	int n;

	if (s != 0) {
		n = *(int *)(s + 0x1c);
		if (n != 0 && *(int *)(s + 0x24) != 0) {
			if (*(int *)(n + 0x14) != 0)
				fcn_004644b0(*(int *)(n + 0x14), s);
			n = *(int *)(s + 0x1c);
			(*(void (__cdecl **)(int, int))(s + 0x24))(*(int *)(s + 0x28), n);
			*(int *)(s + 0x1c) = 0;
			return 0;
		}
	}
	return -2;
}
