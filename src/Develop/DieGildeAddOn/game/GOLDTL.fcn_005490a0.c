/* fcn_005490a0 — run the six subsystem resets, then the final pass. */

void __cdecl he_EnsureCityBuilding0x2bActions(void);
void __cdecl he_EnsureCityAction0x86And0xa2(void);
void __cdecl he_TriggerAction0x67(void);
void __cdecl he_ClearDunkleEcke(void);
void __cdecl he_PruneStammtischSeats(void);
void __cdecl gm_RolloverBuilding0x16Stats(void);
void __cdecl he_EnsureAhmAction0x98(void);

/* ADDRESS: GOLDTL 0x005490a0 */
void __cdecl he_RunDailyActionMaintenance(void)
{
	he_EnsureCityBuilding0x2bActions();
	he_EnsureCityAction0x86And0xa2();
	he_TriggerAction0x67();
	he_ClearDunkleEcke();
	he_PruneStammtischSeats();
	gm_RolloverBuilding0x16Stats();
	he_EnsureAhmAction0x98();
}
