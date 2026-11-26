

char* __cdecl fcn_005b1a80(int);

void __cdecl hp_SetProdSettingScale(char* entity, int scaleBits)
{
	char* setting;

	setting = fcn_005b1a80(*(int*) (entity + 1));
	if (setting != 0) {
		*(int*) (setting + 0x44) = scaleBits;
	}
}
