extern char flt_1_0[];


/* fcn_005a8a30: p=fcn_005b1b10(*(int*)(a+1)); return p ? *(float*)(p+0x38) : *(float*)0x6628a0. */

int __cdecl hp_FindProdSetting(int);

/* ADDRESS: GOLDDE 0x005968b0 */
float __cdecl hp_GetProdSellPriceFactor(char* a)
{
	int p;
	p = hp_FindProdSetting(*(int*) (a + 1));
	if (p != 0) {
		return *(float*) (p + 0x38);
	}
	return *(float*) &flt_1_0;
}
