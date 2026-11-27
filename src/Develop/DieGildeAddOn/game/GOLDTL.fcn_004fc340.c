


#include "Develop/DieGildeAddOn/game/game_data.h"
extern const double g_6640f8;

void __cdecl gm_GetLawEntry(int, int*);

double __cdecl gm_CalcLaw00And01Factor(void)
{
	int a[9];
	int b[9];

	gm_GetLawEntry(0, a);
	gm_GetLawEntry(1, b);
	return (4 - a[6]) * 0.25f * g_6640f8 + (1 - b[6]) * 0.25;
}
