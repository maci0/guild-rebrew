extern char g_14b5730[];
void __cdecl d2_RunGraveyardPickerDialog(int, int, int, int, int);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDTL 0x0058fa20 */
/* ADDRESS: GOLDDE 0x005756e0 */
void __cdecl d2_RunLiegeplanDialog(int p)
{
	d2_RunGraveyardPickerDialog(0, p, *(int*) &g_14b5730, 0, 0);
	d3_EndCameraAndUiMode();
}
