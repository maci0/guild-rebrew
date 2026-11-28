extern unsigned char gm_ActiveTownIndex;

int __cdecl gm_GetSeasonTreasury(int, char);
int __cdecl gm_AmountToUnits(int, char);


/* ADDRESS: GOLDTL 0x004b47a0 */
/* ADDRESS: GOLDDE 0x004a2a90 */
int __cdecl gm_HasMinEntityGold(int entity, char* spec)
{
	return gm_AmountToUnits(gm_GetSeasonTreasury(entity, (*(char*)&gm_ActiveTownIndex)), (*(char*)&gm_ActiveTownIndex)) >= *(int*) (spec + 0x14);
}
