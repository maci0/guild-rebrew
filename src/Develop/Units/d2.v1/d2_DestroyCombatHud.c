extern char g_772f14[];
void __cdecl d2_DestroyForm(int);
void __cdecl cut_ClearStatusOverlaySlots(void);
void __cdecl d2_ClearCombatHudSlots(void);

/* ADDRESS: GOLDTL 0x004d7f70 */
/* ADDRESS: GOLDDE 0x004c4ec0 */
void __cdecl d2_DestroyCombatHud(void)
{
    d2_DestroyForm(*(unsigned int*) &g_772f14);
    *(unsigned int*) &g_772f14 = 0;
    cut_ClearStatusOverlaySlots();
    d2_ClearCombatHudSlots();
}
