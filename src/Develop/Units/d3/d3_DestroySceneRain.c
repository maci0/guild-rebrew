/* fcn_004e4c60 — release the global handle when the status slot is clear. */
extern char cut_SkipMode[];
void __cdecl d3_DestroyRain(int);

/* ADDRESS: GOLDTL 0x004e4c60 */
void __cdecl d3_DestroySceneRain(void)
{
	if (*(int*) &cut_SkipMode == 0) {
		d3_DestroyRain(*(int*) 0x772f6c);
		*(int*) 0x772f6c = 0;
	}
}
