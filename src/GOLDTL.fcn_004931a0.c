#include "Develop/DieGildeAddOn/game/spiel.h"
/* declared float here: the float return is what gives fcomp m32 against p */
float __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLDTL 0x004931a0 */

int __cdecl fcn_004931a0(char* a, char* b)
{
	double da;
	float p;

	da = fcn_00507f10(a, 3);
	p = (float) (da - fcn_00507f10(b, 3) * 0.5 + 0.1f);
	if (gm_RandomFloat01() > p)
		return 0;
	return 1;
}
