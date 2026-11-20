

void __cdecl d2_ClearRadioGroup(int);

void __cdecl fcn_004be360(void)
{
	if (*(int*) 0x6816d8 != -1) {
		d2_ClearRadioGroup(*(int*) 0x6816d8);
	}
	*(int*) 0x6816d8 = -1;
}
