#ifdef REBREW_GOLD
void __cdecl fcn_0046e700(int slot);
#else
void __cdecl fcn_0046b2b0(int slot);
#endif

/* ADDRESS: GOLD 0x0046c9d0 */
/* ADDRESS: GOLDTL 0x00469880 */
void __cdecl fcn_00469880(int slot)
{
#ifdef REBREW_GOLD
	fcn_0046e700(slot);
#else
	fcn_0046b2b0(slot);
#endif
}
