/* fcn_005490a0 — run the six subsystem resets, then the final pass. */

void __cdecl he_EnsureCityBuilding0x2bActions(void);
void __cdecl fcn_005472a0(void);
void __cdecl fcn_00548d50(void);
void __cdecl fcn_005475c0(void);
void __cdecl he_PruneStammtischSeats(void);
void __cdecl gm_RolloverBuilding0x16Stats(void);
void __cdecl fcn_005473a0(void);

/* ADDRESS: GOLDTL 0x005490a0 */
void __cdecl fcn_005490a0(void)
{
	he_EnsureCityBuilding0x2bActions();
	fcn_005472a0();
	fcn_00548d50();
	fcn_005475c0();
	he_PruneStammtischSeats();
	gm_RolloverBuilding0x16Stats();
	fcn_005473a0();
}
