extern char g_7728e4[];
#include "Develop/DieGildeAddOn/game/ambient_animal_slot.h"


void* __cdecl m_alloc(int, void*);

/* ADDRESS: GOLDDE 0x004a9c70 */
void __cdecl gm_AllocAmbientAnimals(void)
{
	void* p;

	p = m_alloc(0x2480, "anm:animals");
	g_7728e8 = (AMBIENT_ANIMAL_SLOT*) p;
	*(int*) &g_7728e4 = 0;
	((AMBIENT_ANIMAL_SLOT*) p)->objekt = 0;
}
