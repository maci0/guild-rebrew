// FUNCTION: GOLDTL 0x506df0
// SIZE: 47
// gm_IsInRange

int __cdecl gm_MapEntityStatRange(int);

int __cdecl gm_IsInRange(int x)
{
	int stat_range;
	stat_range = gm_MapEntityStatRange(x);
	if (stat_range >= 10 && stat_range <= 14) {
		return 0;
	}
	return 2;
}

// FUNCTION: GOLDTL 0x506e10
// SIZE: 6
int __cdecl fcn_00506e10(void)
{
	return 2;
}
