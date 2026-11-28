

char* __cdecl hp_FindProdSettingNode(int);

/* ADDRESS: GOLDDE 0x005968d0 */
void __cdecl hp_SetProdSettingScale(char* entity, int scaleBits)
{
	char* setting;

	setting = hp_FindProdSettingNode(*(int*) (entity + 1));
	if (setting != 0) {
		*(int*) (setting + 0x44) = scaleBits;
	}
}
