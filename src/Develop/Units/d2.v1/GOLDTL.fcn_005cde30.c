

extern int g_14a5550;

void __cdecl d2_RunAmtChamberMenu(void*, int, int);
void __cdecl d3_EndCameraAndUiMode(void);
void __cdecl d2_RunAmtCandidatesDialog(void);

void __cdecl d2_RunAmtCandidatesMenu(void)
{
	d2_RunAmtChamberMenu((void*) d2_RunAmtCandidatesDialog, g_14a5550, 1);
	d3_EndCameraAndUiMode();
}
