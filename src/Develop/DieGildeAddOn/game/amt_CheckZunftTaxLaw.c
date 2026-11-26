extern int __cdecl he_StartHandlungSearch(int, int, int);
extern void __cdecl amt_calc_zuenfte(int);
extern void* __cdecl gm_StartFilteredEntitySearch(int, int, int);

/* ADDRESS: GOLDTL 0x004eb180 */
int __cdecl amt_CheckZunftTaxLaw(int rankRange)
{
	int officeType;
	void* officeRec;

	if (he_StartHandlungSearch(1, 0, 0x80) != 0) {
		amt_calc_zuenfte(0x1e);
		amt_calc_zuenfte(0x1f);
		amt_calc_zuenfte(0x20);
		amt_calc_zuenfte(0x21);
		return 0;
	}
	switch (rankRange) {
	case 1:
		officeType = 0x18;
		break;
	case 2:
		officeType = 0x19;
		break;
	case 3:
		officeType = 0x1a;
		break;
	case 4:
		officeType = 0x17;
		break;
	case 5:
		return 0;
	default:
		goto ret0;
	}
	officeRec = gm_StartFilteredEntitySearch(1, 5, officeType);
	if (officeRec == 0 || (((unsigned char*) officeRec)[0x5a] & 1))
		return 0;
	return 1;
ret0:
	return 0;
}
