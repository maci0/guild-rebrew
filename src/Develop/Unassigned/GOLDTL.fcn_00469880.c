#ifdef REBREW_GOLD
void __cdecl fcn_0046e700(int slot);
#else
void __cdecl d2_DestroyElement(int slot);
#endif

/* ADDRESS: GOLDTL 0x00469880 */
void __cdecl fcn_00469880(int slot)
{
#ifdef REBREW_GOLD
	fcn_0046e700(slot);
#else
	d2_DestroyElement(slot);
#endif
}
