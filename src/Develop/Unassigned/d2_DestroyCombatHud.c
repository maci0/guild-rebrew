void __cdecl d2_DestroyForm(int);
void __cdecl cut_ClearStatusOverlaySlots(void);
void __cdecl d2_ClearCombatHudSlots(void);

/* ADDRESS: GOLDTL 0x004d7f70 */
void __cdecl d2_DestroyCombatHud(void)
{
    d2_DestroyForm(*(unsigned int*) 0x772f14);
    *(unsigned int*) 0x772f14 = 0;
    cut_ClearStatusOverlaySlots();
    d2_ClearCombatHudSlots();
}
