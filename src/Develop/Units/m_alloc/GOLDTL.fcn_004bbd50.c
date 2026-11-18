#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"


void __cdecl m_FreeTracked(void*);

void __cdecl fcn_004bbd50(void)
{
	if (g_7728e8 != 0) {
		m_FreeTracked(g_7728e8);
		g_7728e8 = 0;
	}
}
