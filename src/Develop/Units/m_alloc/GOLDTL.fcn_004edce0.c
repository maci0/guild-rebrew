

#include "g_772f90.h"

#include "Develop/DieGildeAddOn/game/game_data.h"
extern ALCHEMY_PLAYER_PROTOTYPE* g_772fdc;
extern int g_772fe0;
extern ALCHEMY_RECIPE_PROTOTYPE* g_772fe4;

void __cdecl m_FreeTracked(int);

void __cdecl fcn_004edce0(void)
{
	if (g_772fdc != 0) {
		m_FreeTracked((int) g_772fdc);
		g_772fdc = 0;
	}
	if (g_772fe4 != 0) {
		m_FreeTracked((int) g_772fe4);
		g_772fe4 = 0;
	}
	g_772fe0 = 0;
	ahm_PlayerPrototypeCount = 0;
}
