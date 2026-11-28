extern int g_772f2c;
void __cdecl cut_ResolveSimpleCombat(void*);
void __cdecl cut_RunTacticalCombat(void*);

/* ADDRESS: GOLDTL 0x004da170 */
/* ADDRESS: GOLDDE 0x004c6e60 */
void __cdecl cut_SkipCombatCutscene(void* p)
{
	if (g_772f2c == 0) {
		cut_ResolveSimpleCombat(p);
		return;
	}
	cut_RunTacticalCombat(p);
}
