


extern char* gm_MarketEntity;

char* __cdecl gm_QueryEntities(int obj, int mode, ...);

/* ADDRESS: GOLDDE 0x004ef090 */
char* __cdecl gm_FindCityItemHolder(int who)
{
	char* list[8];
	int i;

	if (gm_MarketEntity == 0) {
		return 0;
	}
	list[0] = gm_QueryEntities(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x92);
	list[1] = gm_QueryEntities(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x93);
	list[2] = gm_QueryEntities(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x94);
	list[3] = gm_QueryEntities(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x95);
	list[4] = gm_QueryEntities(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x96);
	list[5] = gm_QueryEntities(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x97);
	list[6] = gm_QueryEntities(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x2db);
	list[7] = 0;
	for (i = 0; list[i] != 0; i++) {
		if (gm_QueryEntities(*(int*) (list[i] + 0x14), 2, 6, 0, who) != 0) {
			return gm_QueryEntities(*(int*) (list[i] + 0x14), 1, 0, 0x116);
		}
	}
	return 0;
}
