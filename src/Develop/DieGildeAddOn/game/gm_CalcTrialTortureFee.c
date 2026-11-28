#include <math.h>

#pragma intrinsic(log10)

extern unsigned char gm_ActiveTownIndex;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl gm_AmountToUnits(int a, unsigned char b);

/* ADDRESS: GOLD 0x494820 */
/* ADDRESS: GOLDTL 0x00493e50 */
/* ADDRESS: GOLDDE 0x00482ca0 */
int __cdecl gm_CalcTrialTortureFee(unsigned short* accuser, unsigned short* accused)
{
	int x;
	int y;
	double v;

	x = gm_CalcPersonWealth(*accuser);
	y = gm_CalcPersonWealth(*accused);
	v = gm_AmountToUnits(y, gm_ActiveTownIndex) + gm_AmountToUnits(x, gm_ActiveTownIndex);
	if (10000.0 > v) {
		v = 10000.0;
	}
	v = v / (log10(v) + 1.0) * 0.05f;
	return (int) (v * 32);
}
