

int __cdecl sb_LoadSampleBank(void);

int __cdecl fcn_004e4ac0(void)
{
	if (*(int*) 0x772f3c != 0) {
		return 0;
	}
	return sb_LoadSampleBank();
}
