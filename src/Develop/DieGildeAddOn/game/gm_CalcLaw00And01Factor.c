


#include "Develop/DieGildeAddOn/game/game_data.h"
extern const double dbl_0_75;

void __cdecl gm_GetLawEntry(int, int*);

/* ADDRESS: GOLDDE 0x004e7eb0 */
double __cdecl gm_CalcLaw00And01Factor(void)
{
	int a[9];
	int b[9];

	gm_GetLawEntry(0, a);
	gm_GetLawEntry(1, b);
	return (4 - a[6]) * 0.25f * dbl_0_75 + (1 - b[6]) * 0.25;
}
