
// fcn_00503f30 — r=fcn_00504ad0(a); return (r in [0xa,0xe]) ? 0 : 2.

#include "spiel.h"

int __cdecl fcn_00503f30(int a)
{
	int r;
	r = gm_MapEntityStatRange(a);
	if (r >= 0xa && r <= 0xe) {
		return 0;
	}
	return 2;
}

/* ADDRESS: GOLDTL 0x00506df0 */
// gm_IsInRange



int __cdecl gm_IsInRange(int x)
{
	int stat_range;
	stat_range = gm_MapEntityStatRange(x);
	if (stat_range >= 10 && stat_range <= 14) {
		return 0;
	}
	return 2;
}

/* ADDRESS: GOLDTL 0x00506e10 */
int __cdecl fcn_00506e10(void)
{
	return 2;
}
