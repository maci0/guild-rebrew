// FUNCTION: GOLD 0x00503f30
// SIZE: 32
// fcn_00503f30 — r=fcn_00504ad0(a); return (r in [0xa,0xe]) ? 0 : 2.

int __cdecl fcn_00504ad0(int);

int __cdecl fcn_00503f30(int a)
{
	int r;
	r = fcn_00504ad0(a);
	if (r >= 0xa && r <= 0xe) {
		return 0;
	}
	return 2;
}

// FUNCTION: GOLDTL 0x506df0
// SIZE: 32
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
