

extern int g_14aa190;

void __cdecl d2_RunAmtChamberMenu(void*, int, int);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_RunTagesordnungDialog(void);

/* ADDRESS: GOLDDE 0x005afb80 */
void __cdecl d2_OpenTagesordnungDialog(void)
{
	d2_RunAmtChamberMenu((void*) d2_RunTagesordnungDialog, g_14aa190, 1);
	d3_EndCameraAndUiMode();
}
