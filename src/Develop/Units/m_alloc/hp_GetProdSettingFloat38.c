
// fcn_005a8a30 — p=fcn_005a8690([a+1]); return p ? *(float*)(p+0x38) : *(float*)0x5eb780.

int __cdecl hp_FindProdSetting(int);

float __cdecl hp_GetProdSettingFloat38(char* entity)
{
	int setting;
	setting = hp_FindProdSetting(*(int*) (entity + 1));
	if (setting != 0) {
		return *(float*) (setting + 0x38);
	}
	return *(float*) 0x5eb780;
}
