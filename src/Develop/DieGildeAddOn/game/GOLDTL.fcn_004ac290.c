char* __cdecl fcn_004ac1e0(int);
unsigned short __cdecl gm_RandomMod(int);


/* ADDRESS: GOLDTL 0x004ac290 */
unsigned short __cdecl gm_PickRandomGedichtVariant(int id)
{
	unsigned short variantId;
	char* p;

	variantId = 0x1e2b;
	p = fcn_004ac1e0(id);
	if (p != 0) {
		if (*(int*) (p + 8) == 0)
			variantId = gm_RandomMod(10);
		else
			variantId = gm_RandomMod(10);
	}
	return variantId;
}
