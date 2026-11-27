extern unsigned char g_773d75;

int __cdecl gm_GetSeasonTreasury(int, char);
int __cdecl gm_AmountToUnits(int, char);


/* ADDRESS: GOLDTL 0x004b47a0 */
int __cdecl gm_HasMinEntityGold(int entity, char* spec)
{
	return gm_AmountToUnits(gm_GetSeasonTreasury(entity, (*(char*)&g_773d75)), (*(char*)&g_773d75)) >= *(int*) (spec + 0x14);
}
