#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"


void __cdecl m_FreeTracked(void*);

/* ADDRESS: GOLDDE 0x004a9ca0 */
void __cdecl gm_FreeAmbientAnimalSlots(void)
{
	if (g_7728e8 != 0) {
		m_FreeTracked(g_7728e8);
		g_7728e8 = 0;
	}
}
