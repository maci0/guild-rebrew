

int __cdecl sb_LoadSampleBank(void);

int __cdecl sb_LoadSampleBankIfAllowed(void)
{
	if (*(int*) 0x772f3c != 0) {
		return 0;
	}
	return sb_LoadSampleBank();
}
