


extern char* gm_MarketEntity;

char* __cdecl fcn_00502cd0(int obj, int mode, ...);

char* __cdecl gm_FindCityItemHolder(int who)
{
	char* list[8];
	int i;

	if (gm_MarketEntity == 0) {
		return 0;
	}
	list[0] = fcn_00502cd0(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x92);
	list[1] = fcn_00502cd0(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x93);
	list[2] = fcn_00502cd0(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x94);
	list[3] = fcn_00502cd0(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x95);
	list[4] = fcn_00502cd0(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x96);
	list[5] = fcn_00502cd0(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x97);
	list[6] = fcn_00502cd0(*(int*) (gm_MarketEntity + 0x5d), 1, 0, 0x2db);
	list[7] = 0;
	for (i = 0; list[i] != 0; i++) {
		if (fcn_00502cd0(*(int*) (list[i] + 0x14), 2, 6, 0, who) != 0) {
			return fcn_00502cd0(*(int*) (list[i] + 0x14), 1, 0, 0x116);
		}
	}
	return 0;
}
