

int __cdecl sb_LoadLocalizedSampleBank(void);

int __cdecl sb_LoadLocalizedSampleBankIfAllowed(void)
{
	if (*(int*) 0x772f3c != 0) {
		return 0;
	}
	return sb_LoadLocalizedSampleBank();
}
