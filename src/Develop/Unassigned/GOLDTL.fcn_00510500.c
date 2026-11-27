


void* __cdecl fcn_00502cd0(int, int, int, ...);

int __cdecl gm_GetBuildingBonusTier(char* building)
{
	int n;

	n = 1;
	if (fcn_00502cd0(*(int*) (building + 0x5d), 2, 6, 0, 0x285)) {
		n = 2;
	}
	if (fcn_00502cd0(*(int*) (building + 0x5d), 2, 6, 0, 0x288)) {
		n++;
	}
	return n;
}
