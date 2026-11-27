#ifdef REBREW_GOLD
void __cdecl d2_DestroyGuiElement(int slot);
#else
void __cdecl d2_DestroyElement(int slot);
#endif

/* ADDRESS: GOLDTL 0x00469880 */
void __cdecl d2_RemoveElement(int slot)
{
#ifdef REBREW_GOLD
	d2_DestroyGuiElement(slot);
#else
	d2_DestroyElement(slot);
#endif
}
