#include <math.h>

#pragma intrinsic(log10)

extern unsigned char g_773d75;

#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_0050b710(int a, unsigned char b);

/* ADDRESS: GOLD 0x494820 */
/* ADDRESS: GOLDTL 0x00493e50 */
int __cdecl gm_CalcTrialTortureFee(unsigned short* accuser, unsigned short* accused)
{
	int x;
	int y;
	double v;

	x = gm_WalkEntityChain(*accuser);
	y = gm_WalkEntityChain(*accused);
	v = fcn_0050b710(y, g_773d75) + fcn_0050b710(x, g_773d75);
	if (10000.0 > v) {
		v = 10000.0;
	}
	v = v / (log10(v) + 1.0) * 0.05f;
	return (int) (v * 32);
}
