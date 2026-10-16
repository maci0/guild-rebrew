int __cdecl fcn_004767c0(int, int, int, int, int, int, int);
void __cdecl fcn_005309d0(int, int);

/* ADDRESS: GOLD 0x004e3060 */
void __cdecl fcn_004e3060(void)
{
	int r;

	if (*(int *)0x6f0d8c != 0)
		return;
	r = fcn_004767c0(0, 0, *(short *)0xfb9072, *(short *)0xfb9070, 0x5fea18, 0x5a, 1);
	*(int *)0x6f0da0 = r;
	if ((*(unsigned char *)r & 4) == 0) {
		do {
			fcn_005309d0(0, *(int *)0x60d340 | 0x80);
		} while ((*(unsigned char *)*(int *)0x6f0da0 & 4) == 0);
	}
}
