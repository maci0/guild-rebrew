


void* __cdecl gm_QueryEntities(int, int, int, ...);

/* ADDRESS: GOLDDE 0x004fb220 */
int __cdecl gm_GetBuildingOptionCount(char* building)
{
	int n;

	n = 4;
	if (gm_QueryEntities(*(int*) (building + 0x5d), 2, 6, 0, 0x284)) {
		n = 7;
	}
	if (gm_QueryEntities(*(int*) (building + 0x5d), 2, 6, 0, 0x289)) {
		n += 3;
	}
	return n;
}
