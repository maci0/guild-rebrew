

extern int g_14abd70;

int __cdecl d2_CheckOwnerBlocked(char*);
void __cdecl fcn_0052a0c0(char*, int);
void __cdecl fcn_005bdc30(int, void*, int, void*, int);
void __cdecl d2_RestoreHudAfterDialog(void);
void __cdecl d2_ConfirmUeberfall(void);
void __cdecl sv_ClearObjectSelection(void);

void __cdecl d2_OpenUeberfallDialog(char* a)
{
	if (d2_CheckOwnerBlocked(a) == 0) {
		fcn_0052a0c0(a, 0);
		fcn_005bdc30(4, 0, g_14abd70, (void*) d2_ConfirmUeberfall, 0);
		d2_RestoreHudAfterDialog();
		sv_ClearObjectSelection();
	}
}
