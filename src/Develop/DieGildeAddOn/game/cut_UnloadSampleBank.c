extern char cut_SkipMode[];


int __cdecl sb_ReleaseSampleBank(void);

/* ADDRESS: GOLDDE 0x004d1480 */
int __cdecl cut_UnloadSampleBank(void)
{
	if (*(int*) &cut_SkipMode != 0) {
		return 0;
	}
	return sb_ReleaseSampleBank();
}
