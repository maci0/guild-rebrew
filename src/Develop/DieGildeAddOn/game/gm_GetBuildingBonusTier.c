


void* __cdecl gm_QueryEntities(int, int, int, ...);

int __cdecl gm_GetBuildingBonusTier(char* building)
{
	int n;

	n = 1;
	if (gm_QueryEntities(*(int*) (building + 0x5d), 2, 6, 0, 0x285)) {
		n = 2;
	}
	if (gm_QueryEntities(*(int*) (building + 0x5d), 2, 6, 0, 0x288)) {
		n++;
	}
	return n;
}
