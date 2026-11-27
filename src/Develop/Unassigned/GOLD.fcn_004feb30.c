/* fcn_004feb30 — walk 0x7e3f40..0x7e4b10 (stride 0x2f4); stop on a zero byte. */

int __cdecl gm_UpdateCityMarketAndPrices(int, int);

void __cdecl gm_UpdateAllCityMarkets(void)
{
	int i;
	int p;

	i = 0;
	p = 0x7e3f40;
	do {
		if (*(char *)p == 0)
			break;
		gm_UpdateCityMarketAndPrices(i, 0x770ae0);
		p += 0x2f4;
		i++;
	} while (p < 0x7e4b10);
}
