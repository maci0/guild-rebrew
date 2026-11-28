extern int cut_SkipMode;

void __cdecl d2_SetFormVisibility(int k, int flag);

/* ADDRESS: GOLDTL 0x004e4450 */
/* ADDRESS: GOLDDE 0x004d0e40 */
void __cdecl d2_SetFormVisibilityIfAllowed(int k, int flag)
{
	if (cut_SkipMode != 0) {
		*(float*) &flag = 0.0f;
	}
	d2_SetFormVisibility(k, flag);
}
