extern char cut_SkipMode[];


int __cdecl sb_LoadLocalizedSampleBank(void);

/* ADDRESS: GOLDDE 0x004d1460 */
int __cdecl sb_LoadLocalizedSampleBankIfAllowed(void)
{
	if (*(int*) &cut_SkipMode != 0) {
		return 0;
	}
	return sb_LoadLocalizedSampleBank();
}
