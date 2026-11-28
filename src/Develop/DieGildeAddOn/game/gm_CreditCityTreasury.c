extern unsigned char gm_ActiveTownIndex;



char* __cdecl gm_GetGuildHall(int);
char* __cdecl gm_QueryEntities(int, int, int, ...);
void __cdecl cm_RequestTransferCurrencyNoKill(int, int, char, int);

/* ADDRESS: GOLDDE 0x004fa650 */
void __cdecl gm_DebitCityTreasury(int amount)
{
	char* e;
	char* r;

	e = gm_GetGuildHall(1);
	r = gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, 0x115);
	cm_RequestTransferCurrencyNoKill(-1, *(int*) (r + 2), (*(char*)&gm_ActiveTownIndex), amount);
}
