char* __cdecl gm_GetBardEventEntry(int);
unsigned short __cdecl gm_RandomMod(int);


/* ADDRESS: GOLDTL 0x004ac290 */
/* ADDRESS: GOLDDE 0x0049a5d0 */
unsigned short __cdecl gm_PickRandomGedichtVariant(int id)
{
	unsigned short variantId;
	char* p;

	variantId = 0x1e2b;
	p = gm_GetBardEventEntry(id);
	if (p != 0) {
		if (*(int*) (p + 8) == 0)
			variantId = gm_RandomMod(10);
		else
			variantId = gm_RandomMod(10);
	}
	return variantId;
}
