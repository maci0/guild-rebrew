void __cdecl d2_RunGraveyardPickerDialog(int, int, int, int, int);
void __cdecl d3_EndCameraAndUiMode(void);

/* ADDRESS: GOLDTL 0x0058fa20 */
void __cdecl d2_RunLiegeplanDialog(int p)
{
	d2_RunGraveyardPickerDialog(0, p, *(int*)0x14b5730, 0, 0);
	d3_EndCameraAndUiMode();
}
