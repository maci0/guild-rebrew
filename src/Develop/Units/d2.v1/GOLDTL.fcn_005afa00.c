


int __cdecl d2_CheckOwnerBlocked(int);
void __cdecl fcn_0052a0c0(int, int);
void __cdecl fcn_005bdc30(int, int, int, void*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl sv_ClearObjectSelection(void);
void __cdecl d2_ConfirmPatrol(void);
extern int g_14abcdc;

void __cdecl d2_SelectPatrolTarget(int building)
{
	if (d2_CheckOwnerBlocked(building) == 0 && building != 0) {
		fcn_0052a0c0(building, 0);
		fcn_005bdc30(4, 0, g_14abcdc, d2_ConfirmPatrol, 0);
		d2_RestoreHudAfterDialog();
		sv_ClearObjectSelection();
	}
}
