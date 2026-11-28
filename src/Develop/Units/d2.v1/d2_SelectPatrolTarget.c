


int __cdecl d2_CheckOwnerBlocked(int);
void __cdecl d2_InitPlayerBar(int, int);
void __cdecl d2_RunCityScrollMapDialog(int, int, int, void*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);
void __cdecl d2_ConfirmPatrol(void);
extern int g_14abcdc;

/* ADDRESS: GOLDDE 0x00594400 */
void __cdecl d2_SelectPatrolTarget(int building)
{
	if (d2_CheckOwnerBlocked(building) == 0 && building != 0) {
		d2_InitPlayerBar(building, 0);
		d2_RunCityScrollMapDialog(4, 0, g_14abcdc, d2_ConfirmPatrol, 0);
		d2_RestoreHudAfterDialog();
		sv_ClearObjectSelection();
	}
}
